# Building with Docker

```
$ docker build -t svaroskey:latest .
$ docker run --rm -v $(pwd):/build -u $(id -u) svaroskey:latest make [clean] # or ./script/dmake [clean]
```
