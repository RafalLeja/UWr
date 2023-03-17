/*


*/

using System;
using System.Collections;

namespace fibonacci
{
    class Slowo
    {
        public string val;

        public Slowo(int n)
        {
            if(n==1) 
            {
                this.val = "b";
                return;
            }else if(n==2)
            {
                this.val = "a";
                return;
            }else
            {
                string s2 = "b";
                string s1 = "a";
                string s0 = "";
                for (int i = 0; i < n; i++)
                {
                    s0 = s1 + s2;
                    s2 = s1;
                    s1 = s0;
                }
                this.val = s0;
            }
        }
    }

    class SlowaFibonacciego : IEnumarable
    {
        private Slowo[] _slowa;
        public SlowaFibonacciego(int n);

    }
}