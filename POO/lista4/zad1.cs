using System;
using System.Threading;

public class ProcessSingleton
{
    private static ProcessSingleton _instance;
    private static readonly object _lock = new object();

    private ProcessSingleton() { }

    public static ProcessSingleton Instance
    {
        get
        {
            lock (_lock)
            {
                if (_instance == null)
                {
                    _instance = new ProcessSingleton();
                }
                return _instance;
            }
        }
    }
}

public class ThreadSingleton
{
    private static ThreadLocal<ThreadSingleton> _threadInstance = new ThreadLocal<ThreadSingleton>(() => new ThreadSingleton());

    private ThreadSingleton() { }

    public static ThreadSingleton Instance => _threadInstance.Value;
}

public class TimedSingleton
{
    private static TimedSingleton _instance;
    private static readonly object _lock = new object();
    private static long _lastInstanceTime;

    private TimedSingleton() { }

    public static TimedSingleton Instance
    {
        get
        {
            long currentTime = DateTimeOffset.UtcNow.ToUnixTimeSeconds();
            lock (_lock)
            {
                if (_instance == null || currentTime - _lastInstanceTime > 5)
                {
                    _instance = new TimedSingleton();
                    _lastInstanceTime = currentTime;
                }
                return _instance;
            }
        }
    }
}

class Program
{
    static void Main(string[] args)
    {
        // Testy jednostkowe
        TestProcessSingleton();
        TestThreadSingleton();
        TestTimedSingleton();
    }

    static void TestProcessSingleton()
    {
        ProcessSingleton singleton1 = ProcessSingleton.Instance;
        ProcessSingleton singleton2 = ProcessSingleton.Instance;

        Console.WriteLine("Process Singleton Test:");
        Console.WriteLine($"Are instances equal: {singleton1 == singleton2}");
    }

    static void TestThreadSingleton()
    {
        Thread thread1 = new Thread(() =>
        {
            ThreadSingleton singleton1 = ThreadSingleton.Instance;
            Console.WriteLine($"Thread 1 - Singleton1 Instance Hash Code: {singleton1.GetHashCode()}");

            ThreadSingleton singleton2 = ThreadSingleton.Instance;
            Console.WriteLine($"Thread 1 - Singleton2 Instance Hash Code: {singleton1.GetHashCode()}");
        });

        Thread thread2 = new Thread(() =>
        {
            ThreadSingleton singleton1 = ThreadSingleton.Instance;
            Console.WriteLine($"Thread 2 - Singleton1 Instance Hash Code: {singleton1.GetHashCode()}");

            ThreadSingleton singleton2 = ThreadSingleton.Instance;
            Console.WriteLine($"Thread 2 - Singleton2 Instance Hash Code: {singleton1.GetHashCode()}");
        });

        thread1.Start();
        thread2.Start();

        thread1.Join();
        thread2.Join();
    }

    static void TestTimedSingleton()
    {
        TimedSingleton singleton1 = TimedSingleton.Instance;
        Thread.Sleep(6000); // Wait for 6 seconds
        TimedSingleton singleton2 = TimedSingleton.Instance;

        Console.WriteLine("Timed Singleton Test:");
        Console.WriteLine($"Are instances equal: {singleton1 == singleton2}");
    }
}
