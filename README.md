# text-formatter
**Formats words to the N column of a text**

### Example
Using `text-formatter -c 50 -f test/test2.txt`, it move to the next line all the
words that are past the column 50 of the file test/test2.txt.
```bash
# Original
Lorem ipsum dolor sit amet, consectetur adipiscing elit. Facile est
hoc cernere et primis puerorum aetatulis.
Paupertas malum est, mendicus beatus esse nemo potest, quamvis sit sapiens.
Affectus, orbus.
                                                  ^ !!!!!!!!!!!!!!!!!!!!! ^
                                          col 50 ^

# Final
Lorem ipsum dolor sit amet, consectetur adipiscing
elit. Facile est
hoc cernere et primis puerorum aetatulis.
Paupertas malum est, mendicus beatus esse nemo
potest, quamvis sit sapiens.
Affectus, orbus.
```
*Note that with `-c 85` (Which is the default) it will admit words whose last
character is less **or equal** than 85.*

### Building
Simply run:
```console
$ git clone https://github.com/r4v10l1/text-formatter

$ cd text-formatter

$ make
...

$ ./text-formatter -h
Usage:
    ./text-formatter               - Format stdin to stdout
    ./text-formatter -c <cols>     - Specify the max column number
    ./text-formatter -f <file>     - Read from file and write to stdout
    ./text-formatter -f <file> -i  - Read from file and write in-place (to that same file)
```

### Installing
For adding the program to the path, run:
```console
$ sudo make install
...
```

### Todo
- [ ] Add `-i` option.

