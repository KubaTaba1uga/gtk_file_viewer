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
