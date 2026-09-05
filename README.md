# C File Parser

A small C program that parses a text file containing content/value pairs and converts them into a C array of `Lyric` structures.

## Input format

The input file uses the following format:

```text
ur text[10]
and each duration [20.3]
will be converted to a C array
errors will be logged [22]

==> to

Lyric lyrics[] = {
    {"ur text", 10.0f},
    {"and each duration", 20.3f},
    {"will be converted to a C array", 22.0f},
    {"errors will be logged", 43.232f}
};