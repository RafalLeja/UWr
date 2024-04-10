using System;
using System.IO;


public interface ILogger {
  void Log( string Message );
}

public class NoneLogger : ILogger {
  public void Log( string Message ) { }
}

public class ConsoleLogger : ILogger {
  public void Log( string Message ) {
    Console.WriteLine( Message );
  }
}

public class FileLogger : ILogger {
  private string Path;
  public FileLogger( string Path ) {
    this.Path = Path;
  }

  public void Log( string Message ) {
    File.AppendAllText( Path, Message + "\n" );
  }
}

public enum LogType { 
  None, 
  Console, 
  File 
}

public class LoggerFactory {
  public ILogger GetLogger( LogType LogType, string Parameters = null ) { 
    switch( LogType ) {
      case LogType.None: return new NoneLogger();
      case LogType.Console: return new ConsoleLogger();
      case LogType.File: return new FileLogger( Parameters );
      default: throw new ArgumentException();
    }
  }

  public static LoggerFactory Instance { get; } = new LoggerFactory();
}
// klient:

public class Client {
  public static void Main() {
    ILogger logger1 = LoggerFactory.Instance.GetLogger( LogType.File, ".\\foo.txt" );
    logger1.Log( "foo bar" ); // logowanie do pliku
    ILogger logger2 = LoggerFactory.Instance.GetLogger( LogType.None );
    logger2.Log( "qux" ); // brak logowania
  }
}