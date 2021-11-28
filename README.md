


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