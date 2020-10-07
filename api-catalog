# Viskuausan
Glósur 
```
ekki keyra "docker desktop" fara bara í powersshell as admin og keyra
docker version til að tékka hvort einhver villa sé í gangi

Búa til container
	opna git bash
	cd  ~/source/repos/StafraentIsland/island.is
    docker-compose -f ./libs/api-catalogue/elastic/elastic.yml up


eftir að hann er kominn í gang opna git bash í rót island.is
	add data
		cd  ~/source/repos/StafraentIsland/island.is
		h
	
 

	DIGIS-105 Skrá task sem scheduler
 
		til að kerya x-road collector
			þarft að vera með elastic docker keyrandi
	
		services/xroad collector
			breyta línu 14 í C:\Users\gudjons\source\repos\StafraentIsland\island.is\libs\api-catalogue\consts\src\lib\providerType.ts
				úr "  PROTECTED = 'protected'," í "service" 
		keyra: 
			yarn nx run services-xroad-collector:serve
		
		Til að prófa svo hvort þetta sé komið í elastic geturu gert í command line::
			curl http://localhost:9200/apicatalogue/_search
	
		
starta graphql
	 yarn start api
	 
	starta síðu
	cd  source/repos/StafraentIsland/island.is
	 //yarn start api eða nx serve api
	 
	 
	 docker run -p 9100:9100 -e POSTGRES_PASSWORD=postgres --name postgres postgres
   
```
