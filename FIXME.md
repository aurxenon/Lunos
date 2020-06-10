# Broken/Unfinished Bits of Code

**Project-Wide**
* Comment things so that even a C++ noob can understand, but don't get in the way of reading the code itself
* Refactor poorly written / hacky bits of code
* Unwinding functionality????

**Libs/LibLunos**
* C-string comparisons and thus C++ string comparisons are broken
* Vector's are VERY unfinished, and are missing Iterators
* More of the STL needs to be implemented in general, especially data structures

**Kernel/Drivers**
* Serial drivers don't work at all
* Create a framework similar to Linux's __define_initcall so drivers can be dynamically loaded
* Rewrite the old drivers to take advantage of the new driver classes
* Fix any stubs
* Raw framebuffer drawing would be useful for non-BIOS systems
* CMOS needs to check if the time is updating before it reads

**Kernel/Arch/x86/**
* Paging needs to be extended so that the full range of memory can be taken advantage of

**Kernel/Arch**
* It would be good to start attempting ports to other architectures early on before the system becomes too x86-dependent