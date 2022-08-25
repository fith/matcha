# Matcha: Hog & Sandwich

Matcha is a match-3 game where the goal is to move a hungry hedgehog across the board to a sandwich.

The hedgehog and sandwich can move to like-color dots. Hog will indicate this by running towards a friendly neighboring dot.

Get them to the food in the least number of moves. Ideally under par. Levels are seeded, so they're always the same puzzle.

The music is me humming. SFX were also made with my mouth. I think the original hedgehog graphic is stolen from Google images, sorry, but I animated it.

This was my first C and SDL project ever, so it's pretty rough internally. I wanted to finish it, but it was also my first time usin Conan and Cmake, so to be honest after an update that borked my toolchain I forgot how to get it it to build.

![Alt text](/../main/design/screenshot.png?raw=true "Matcha")

Uses the wonderful single header library STB: https://github.com/nothings/stb

## Pre-Requisites

### Install Conan


### Add Conan Remotes


Add remote for Bincrafters SDL2:
```
conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
```
or maybe
```
conan remote update bincrafters https://bincrafters.jfrog.io/artifactory/api/conan/public-conan
```

Enable Revisions
```
 conan config set general.revisions_enabled=1
 ```
(https://bincrafters.github.io/2020/04/19/infrastructure-changes-and-required-actions/)
