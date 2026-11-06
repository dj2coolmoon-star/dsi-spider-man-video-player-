# Spider-Verse DSi Video Hub

An original Nintendo DS/DSi homebrew project with a Spider-Verse-inspired red/black text interface.

## Current status

This is an **early source-code prototype**, not a finished video player and not a compiled `.nds` file.

Included now:
- DSi SD-card initialization
- Creates/reads an `Videos` folder on the SD card
- Lists `.fv` video files
- UP/DOWN selection, A to select, X to rescan, START to exit

Not included yet:
- Video decoding or playback
- Pause/seek controls
- Custom graphics and animation

The Nintendo DS/DSi cannot play arbitrary MP4 files directly. A playback engine and a supported video format are required. This prototype deliberately does not pretend that selecting a file plays it.

## Build environment

This project is intended for **BlocksDS** and its Wonderful Toolchain on Windows.

The easiest reliable starting point is to copy the official BlocksDS `rom_arm9` template and place this repository's `source/main.c` in its `source` folder. Keep the template's Makefile and build files. Then change the template's `NAME`, `GAME_TITLE`, `GAME_SUBTITLE`, and `GAME_AUTHOR` values to:

- `NAME := spiderverse_video_hub`
- `GAME_TITLE := SpiderVerse Video Hub`
- `GAME_SUBTITLE := DSi Video Library`
- `GAME_AUTHOR := Original homebrew project`

Build from the **Wonderful Toolchain Shell** with:

```sh
make
```

The official BlocksDS first-program tutorial explains templates and building:
https://blocksds.skylyrac.net/tutorial/basic/first_program/

Filesystem documentation:
https://blocksds.skylyrac.net/docs/guides/filesystem/

## SD card

Create this folder on the DSi SD card:

```text
/ Videos
```

Use the actual folder name `Videos` with no space. Put supported `.fv` files there. The prototype only lists these files; playback is not implemented yet.

## GitHub upload

Create a new empty repository on GitHub, then choose **Add file → Upload files** and upload the contents of this folder (not the ZIP file itself). Commit the upload.

## License

MIT. See `LICENSE`.
