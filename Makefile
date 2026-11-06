BLOCKSDS ?= /opt/blocksds/core

NAME := spiderverse_video_hub

GAME_TITLE := SpiderVerse Video Hub
GAME_SUBTITLE := DSi Homebrew
GAME_AUTHOR := SpiderVerse

SOURCEDIRS := SpiderVerse-DSi-Video-Hub-GitHub-Starter/source
LIBS := -lnds9

include $(BLOCKSDS)/sys/default_makefiles/rom_arm9/Makefile
