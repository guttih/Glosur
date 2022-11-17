# Docker glósur

## Detailed help

- [Docker Documentation](https://docs.docker.com/engine/reference/run)
    -   [run](https://docs.docker.com/engine/reference/commandline/run/)
      | [ps](https://docs.docker.com/engine/reference/commandline/ps/)
      | [container](https://docs.docker.com/engine/reference/commandline/container/)
      | [images](https://docs.docker.com/engine/reference/commandline/images/)
      | [volume](https://docs.docker.com/engine/reference/commandline/volume/)
      | [compose](https://docs.docker.com/compose/reference/)
      | [Dockerfile](https://docs.docker.com/engine/reference/builder/)
    - Create a new image from a container’s changes [commit](https://docs.docker.com/engine/reference/commandline/commit/)
 - Keyboard shortcuts when you are inside a running container
      - `ctrl+p, ctrl+q` Detach from a running container
         - To attach again, type command `docker attach <containerName>`
 - Docker file syntax explained in [linkedin learning](https://www.linkedin.com/learning/learning-docker-2018/dockerfile-syntax?autoSkip=true&autoplay=true&contextUrn=urn%3Ali%3AlyndaLearningPath%3A5bb4fa9b498e2e532e6df920&resume=false)
      

## Highlights
- `docker images` List available docker images
- `docker container ls` List local containers
- `docker ps` List running containers
- `docker ps -a` List all running containers
- `docker --rm -ti <imageName> bash` Remove/delete a container when it has been run
- `docker -d -ti <imageName> bash` Detach from a container, but keep it running
- `docker rm <containerName>` Remove/delete a container with a specific name
- `docker inspect <containerName>` View Info on container
- `docker exec -it <containerName> bash` opna (aðra) shell í ákveðnum docker
- `docker pull postgres` Download docker image called postgres
- `docker-compose up` run docker-compose.yaml file
- `docker run -p 5432:5432 -e POSTGRES_PASSWORD=password --name pg postgres` Run a docker image called postgres and port-forward  port 5432 on that container to port 5432 on host machine(localhost)
- `docker run -p 5050:80 -e PGADMIN_DEFAULT_EMAIL=guttih -e PGADMIN_DEFAULT_PASSWORD=password --name pgadmin -d  dpage/pgadmin4` container sem gefur pgadmin access að databasanum  accessable á localhost:5555. svo þarf að setja gildi í 2 environment variables PGADMIN_DEFAULT_EMAIL og PGADMIN_DEFAULT_PASSWORD
- `docker kill containerID` Turn a docker container off by ID

- Click here to visit [Docker Commands] from docker

### docker glósur vegna raf-isl

projectið : https://github.com/MattiSig/raf-isl
starta projectinu docker-compose up

## New notes created after **2022-11-16**

### Sharing a directory

Directories and files can be shared between 

    - host and container (persistent)
    - container and another container (ephemeral)
#### Share host directory to container (Persistent)

1. On host create a folder and file
    ```shell
        mkdir ~/shared-dir
        echo "Important stuff" >~/shared-dir/important.txt
    ```

2. run a container called **ubuntu** which should have access to this directory
    ```shell
        docker run -ti -v ~/shared-dir:/shared-dir ubuntu bash
    ```
3. Inside the container **ubuntu** add another line file and display its content
    ```shell
        echo "More important stuff" >>/shared-dir/important.txt
         cat /shared-dir/important.txt
    ```

#### Share container directory to another container 

This dir exists while a container is using it (regardless of who created  it)
1. Create a shared directory in container named **ubuntu1** and run the container
    - Run this command on the host machine
        ```shell
            docker run -ti --name ubuntu1 -v /shared-dir2 ubuntu bash
        ```

2. Create access to the shared directory and run container **ubuntu2**
    - Run this command on the host machine
        ```shell
            docker run -ti --name ubuntu2 --volume /shared-dir2 ubuntu bash
            #Alternately access all volumes from a specific container
              #docker run -ti --name ubuntu2 --volumes-from ubuntu1 ubuntu bash
        ```
3. Inside the container **ubuntu2** create a file in the shared folder
    ```shell
        echo "important stuff" >/shared-dir2/important.txt
         cat /shared-dir2/important.txt
    ```
3. Inside the container **ubuntu1** view the content of the shared file
    ```shell
         cat /shared-dir2/important.txt
    ```


### Make docker store images and container on external drive

You can force docker to place it's internal storage/volumes/cache/etc folder on your external drive. Stop docker
 ```shell
sudo service docker stop
 ```

Edit or create the daemon override file
```shell
    sudo vim /etc/docker/daemon.json
```

set /add this to point to your new location
```json
{
"data-root": "/path/to/externaldrive/docker-files"
}
```

At this point you can move the content of docker's default storage location in /var/lib/dockerto your new location, do this if you want to save your existing volumes or images. Then restart docker

```shell
sudo service docker restart
```
[Docker Commands]: https://docs.docker.com/engine/reference/commandline/docker/
