// bwprint.h by Bill Weinman <http://bw.org/>

This code is Copyright (c) 2021 BHG LLC

This code is free and open source without restriction. 

If you find bugs or make enhancements, please contact me at 
https://bw.org/contact

###

Version 0.4a 2021-08-12 – minor fixes 

###

This code requires either the C++20 <format> library, or the libfmt library
from https://fmt.dev/

Once C++23 is released, along with std::print(), this code will become
obsolete. 

###

NOTE BENE: It's generally considered extremely bad practice to add user code
to the std namespace. In this case I chose to violate that rule with the
knowledge that this code will be obsoleted by an equivalent function in C++23.
At that time the user may simply drop this #include file and leave the rest of
their code alone. I think that's a good reason to violate the rule. If you
disagree, simply change the BWP_NAMESPACE macro to whatever name you prefer. 

Have fun! 

//Bill
