# Install dependencies
```
sudo apt update
sudo apt install libgtk-4-dev
```

# Check gtk version
```
pkg-config --modversion gtk4
```

# Fix long loading of window
```
systemctl --user import-environment DISPLAY XAUTHORITY
systemctl --user restart xdg-desktop-portal xdg-desktop-portal-gtk
```

# Run with sanitizers
```
inv build --debug
export LSAN_OPTIONS="$LSAN_OPTIONS suppressions=src/lsan.supp"
./build/gtk_file_viewer
```

If sanitizer output is not equal, the following you have memory leak:
```
-----------------------------------------------------
Suppressions used:
  count      bytes template
      1        640 XGetVisualInfo
-----------------------------------------------------
```

