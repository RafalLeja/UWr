using System;
using System.Collections;
using System.Collections.Generic;

class Program
 {
     /* this is the Comparison<int> to be converted */
     static int IntComparer( int x, int y )
     {
         return x.CompareTo( y );
     }
 
     static void Main( string[] args )
     {
        ArrayList a = new ArrayList() { 1, 5, 3, 3, 2, 4, 3 };

        IComparer comparer = Comparer<int>.Create(IntComparer);

        /* the ArrayList's Sort method accepts ONLY an IComparer */
        a.Sort( comparer );

        foreach( int i in a )
        {
            Console.WriteLine( i );
        }
     }
 }