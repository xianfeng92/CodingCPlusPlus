// !! Utility Conventions

// !! Syntax conventions

Most QNX Neutrino utilities follow standard conventions for argument syntax and behavior. These conventions are based on the utility
conventions outlined in POSIX 1003.2-1992.

The syntax synopsis for each utility appears at the top of the page of its manual entry. 'The utility name appears first, followed by
other allowed command-line arguments, which include options, option arguments(e.g., “number” in -n number), and operands 
(e.g., the names of files to act on)'.


 A typical utility syntax line looks like this:

 utilityname [-abcd] [-o arg | -p arg] infile... outfile

1. The example above shows a utility called utilityname that accepts the options -a, -b, -c, and -d, you can use these options by 
   themselves or in any combination.

2. The utility also accepts the options -o and -p, both of which require an option argument, and which may not be used together 
   (but may be used with the other options -abcd).

3. The utility requires two or more operands: one or more infile and exactly one outfile.


// !! Interpreting utility syntax

'Here are the main principles at work':

1. When utilities have many options, the options may appear grouped together in the syntax like this:

    utilname [-abcd]

   which means that the options -a, -b, -c, and -d are supported.

2. 'Options, option arguments, and operands enclosed in brackets ([ and ]) are optional and can be omitted'. Note that you should 
    never include the [ and ] symbols in the actual command.

3. Arguments separated by | are mutually exclusive. Sometimes mutually exclusive arguments that relate to modes of operation are 
    indicated with multiple syntax lines representing the different forms of the command.

4. A trailing ellipsis mark (…) after options or operands indicates that the preceding item may be repeated. If the preceding item 
   is optional, the ellipsis indicates that the item may occur zero or more times. For example:

    utility [filename...]

   If the item is mandatory, the ellipsis indicates it may occur one or more times. For example:
    
   utility filename...


// !! Invoking utilities

There are a number of general guidelines to follow when running utilities:

1. An option may be followed by another option after a single dash (-) on the command line as long as each preceding option doesn't'
   have an option argument. For example, the option string -abc is equivalent to -a -b -c. However, if -a accepts an option argument, 
   then -abc would be equivalent to -a bc instead.

2. Options and their option arguments should be specified with spacing as shown in their documentation. If the documentation says:

    -n number

   the number should be a separate command-line argument from the -n. But if the documentation refers to:

   -nnumber

   then number should appear in the same argument as -n without any intervening blanks. 

3. Options are usually listed in alphabetical order, but there's no restriction on the order that they may appear in the command line
    when used, unless otherwise indicated in the documentation for the utility. Note that in some utilities, mutually exclusive 
    options override each other in a “last one wins” manner.


4. 'All options and associated option arguments must precede any operands on the command line'. For example, if you want to run the 
    cp utility with the -R option, you may enter:

   cp -R dir1 dir2

   but not:

   cp dir1 dir2 -R

5. The argument -- (“dash dash”) may be placed on the command line 'as a delimiter indicating the end of options and the start of 
   operands'.This is particularly useful when the operands themselves might start with a dash. For example, to remove a file named 
   “-t”, you would use:

   rm -- -t

   Utilities that don't' accept any options also accept and discard a -- before their operands, unless otherwise indicated.


6. Most utilities that accept filenames as operands (and sometimes as option arguments) accept the filename “-” to mean standard 
   input, or, when unambiguous from its context, standard output.


// !! File conventions

'File pathnames specified on the command line are restricted to 255 characters'. Some input files are specifically identified as 
“text files.” Text files are expected to contain ASCII text in newline-terminated lines that don't' exceed 2048 characters, unless 
otherwise indicated.


// !! Signal conventions

Signal actions are inherited from the process that invokes the utility. Most utilities don't do any special processing upon receipt
of a signal, but behave instead according to the system defaults. When a utility performs some action on receipt of a signal other 
than the default, it's documented as doing so.



// !! Exit status conventions

1. Utilities normally return zero for successful completion and values greater than zero when unsuccessful.

2. Some utilities return different nonzero numbers according to the reason they failed. Beware of testing for a specific nonzero 
   number to indicate failure.


// !! Error conventions

Utilities may fail for many reasons, ranging from incorrect usage to underlying system failure. The documentation for the utilities 
doesn't' attempt to outline the exact behavior for all possible modes of failure.

When an error occurs, the utility stops the processing of the current operand and proceeds to process the next operand in the sequence.
'If a utility fails to process one operand but succeeds on others, the exit status still reflects failure'. For utilities that recurse 
through a filesystem (e.g., find), if an action cannot be performed on one file within a hierarchy, the utility stops processing that 
file and goes on to the subsequent files in the hierarchy.