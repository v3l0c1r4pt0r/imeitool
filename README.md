# IMEItool

Handy tool to check/describe/generate IMEI numbers

Overview
--------

imeitool is small utility for POSIX-based systems that can:
* validate IMEI number's checksum
* search its databases for vendor and model that given IMEI/TAC was alloc'd to
* generate fake, valid IMEI number basing on user-provided specification

Usage
-----

```
  -q,  --query IMEI|TAC query databases for given IMEI or TAC
  -n,  --new    generate random IMEI
  -v,  --vendor VENDOR  generate IMEI with TAC allocated by VENDOR
  -m,  --model MODEL    restrict generation to specific MODEL
       --rbi RBI        generate IMEI using specific RBI (cannot be used along
                        with -v and -m)
```

Disclaimer
----------

I am not responsible for any illegal actions that may be done with help of this
software. This tool is intended to be used for finding information about IMEI
and for testing/educational purposes. It is not intended for IMEI-spoofing,
especially in countries that explicitly forbids this practice.

License
-------

This software is distributed AS IS on GNU Lesser General Public License v3.
License does not include any TAC databases included. They are licensed according
to:
* wikipedia - Creative Commons Attribution-ShareAlike License (
[source](https://en.wikipedia.org/wiki/Type_Allocation_Code))
* verified, unverified - Same as whole repository

Contributions
-------------

Because of its simple format (CSV) you could easily create your own database or
add new entries to existing one. If you want to contribute only few numbers,
please use unverified.tac.csv file. If you have bigger database that you want to
contribute here, you can use seperate file to make things clean. All
contributions can be made using Github's pull-request mechanism.
