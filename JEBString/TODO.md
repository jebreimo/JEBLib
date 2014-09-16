Remaining functions
-------------------
glob-matching functions
codepage encodings

C++98 -> C++14
--------------
I can't make the transition until support for VS2010 can be dropped.

Some changes:
* Replace for (auto it = begin(c); ....) with for (auto v: c)
* Include \<utility\> rather than \<algorithm\> for std::swap.