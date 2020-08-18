# Docker glósur
- `docker ps` lista containera í gangi
- `docker ps -a` lista alla containera í gangi
- `docker rm <containerName>` eyða container með ákveðnu nafni
- `docker inspect <containerName>` skoða upplýsingar um container
- `docker exec -it <containerName> bash` opna shell í ákveðnum docker
- `docker pull postgres` sækja docker image sem heitir postgres
- `docker-compose up` keyra docker-compose.yaml file
- `docker run -p 5432:5432 -e POSTGRES_PASSWORD=password --name pg postgres` Keyra upp image sem heitir postgres og porforwarda porti 5432 á container í port 5432 á localhost
- `docker run -p 5050:80 -e PGADMIN_DEFAULT_EMAIL=guttih -e PGADMIN_DEFAULT_PASSWORD=password --name pgadmin -d  dpage/pgadmin4` container sem gefur pgadmin access að databasanum  accessable á localhost:5555. svo þarf að setja gildi í 2 environment variables PGADMIN_DEFAULT_EMAIL og PGADMIN_DEFAULT_PASSWORD
- `docker kill containerID` slökkva á container

- Click here to visit [Docker Commands] from docker



### docker glósur vegna raf-isl
projectið : https://github.com/MattiSig/raf-isl
starta projectinu docker-compose up

#### aðilar sem þekkja
- Hilmar ævar hilmarsson 
- Matthías Sigurbjörnsson


[Docker Commands]: https://docs.docker.com/engine/reference/commandline/docker/
