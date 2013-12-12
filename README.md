#ParanoLog

## What is it?

A work tracker for self quantified paranoids.

Blinks a status icon at a given interval (by default 30 min), and allows the
paranoid to enter what he did since last report. The paranoid can later on
check the reports of what he's been doing.

##Compilation:

### On Linux

```
qmake && make
```

### On Mac OS X

You'll need to install [Inkscape](http://www.inkscape.org) first, as it is
needed to generate the icon bundle. You'll also need XCode to compile the code.

```
./icons/generate_osx_icons.rb
qmake
xcodebuild clean install
```

If you want to make the generated bundle distributable to people who don't have
the Qt frameworks already installed, you need to run the `macdeployqt` tool on
it. See [the documentation of macdeployqt](https://qt-project.org/doc/qt-4.8/deployment-mac.html)
for more information.
