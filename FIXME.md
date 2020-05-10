# Broken/Unfinished Bits of Code

**Libs/LibLunos**
* C-string comparisons and thus C++ string comparisons are broken
* Vector's are VERY unfinished, and are missing Iterators

**Kernel/Drivers**
* Serial drivers don't work at all
* Create a framework similar to Linux's __define_initcall so drivers can be dynamically loaded
* Rewrite the old drivers to take advantage of the new driver classes

**Kernel/Arch/x86/**
* Paging needs to be extended so that the full range of memory can be taken advantage of