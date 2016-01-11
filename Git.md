Git glósur
 ==========
hægri-smella á möppuna í explorer sem projectið á að vistast í og velja git-bash here
 
skrifa í gluggann
 
git clone https://github.com/dthgs/what_sub.git
 
//setja global email og user með þessu
 
git config --global user.email "youremal@gmail.com"
 
git config --global user.name "guttih"
 
svo eftir hverja breytingu þarf að gera
 
git add . (Save)
 
git commit -m "Lýsing á því sem þú gerðir" (committast í þitt local repo)
 
git pull (sækja af netinu)
 
//laga merge ef conflict og þá add-a, commit-a og pull-a aftur.
 
git push (senda upp)
●     Commita oft
●     Gera mörg branches
●     Gera mörg master
●     Eitt aðalbranch (master)
●     Búa til branch fyrir alla fídusa
●     Gera merge master reglulega á branch-inu
●     Sérhvert branch getur innihaldið x-mörg commit
●     Commit-in eiga að vera lítil, litlar breytingar
●     Þegar búið er að útfæra fídusinn, er merge-að branch-ið inní master
●     Ekki óalgengt að henda svo branch-inu þegar það er búið að þjóna sínum tilgangi

 
 
➔     Commit - Tekur kóðann úr einum punkti í annann, inniheldur x-margar skrár sem hafa annaðhvort breyst, bæst við eða dottið út
➔     Push - Sendir breytingar inná miðlæga repository-ið (Bitbucket/GitHub)
➔     Pull - Sækir breytingar frá miðlæga repository-inu (Bitbucket/GitHub)
➔     Branch - Ný hliðstæð útgáfa af kóðanum.. svo er hægt að halda áfram þaðan / Mismunandi útgáfur, svo ekki sé verið að skemma fyrir hvor öðrum / Þegar verið er að fara að útfæra ákveðinn fídus, einn og sér, án þess að hafa áhrif á aðra
➔     Checkout - Svissar á milli brancha

 
http://git-scm.com/downloads
https://github.com/dthgs/project_Skjatexti
★ 	git status - Hver er staðan á working directory
★     git checkout -b my-new-branch - Býr til nýtt branch
★     git checkout master - Skiptir yfir á master
★     git add . - Þannig að hægt sé að commit-a breytingum / Þannig að hægt sé að gera breytingar / "Næst þegar ég commit-a þá eiga þessar breytingar á þessum skrám að fara inn í commit-ið" / Setur skrárnar í 'Staging area' / Þessi breyting á að fara inn í næsta commit
★     git commit -m "Added some files" - Setur skrárnar í repository-ið, localt í hidden .git möppuna / Commenta commit-ið!
★     git push origin master - Sendir allar breytingar sem hafa verið gerðar á master
★     git clone git@github.com:danielbsig/TestApp.git - Klónar projectið / Tekur afrit af kóðanum / Býr til projectið inná GitHub
★     git merge master - Tekur inn breytingar á master, í branch-ið


#ssh
To change beetwen two ssh files saved in config ssh -T bitbuc
f.example if host was bitbuc then this would change to that profile
we are talking about the file ~/.ssh/config
