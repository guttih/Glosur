 ### Skipanir
- Commit
    - Tekur kóðann úr einum punkti í annann, inniheldur x-margar skrár sem hafa annaðhvort breyst, bæst við eða dottið út
- Push
    - Sendir breytingar inná miðlæga repository-ið (Bitbucket/GitHub)
- Pull 
    - Sækir breytingar frá miðlæga repository-inu (Bitbucket/GitHub)
- Branch 
    - Ný hliðstæð útgáfa af kóðanum.. svo er hægt að halda áfram þaðan / Mismunandi útgáfur, svo ekki sé verið að skemma fyrir hvor öðrum / Þegar verið er að fara að útfæra ákveðinn fídus, einn og sér, án þess að hafa áhrif á aðra
- Checkout 
    - Svissar á milli brancha

# Git glósur
- `git remote -v` Skoða slóða að origin `https://github.com/Hubar/ticktacktoe.git`
- `git remote` skoða hvaða remote þú ert tengdur.. þ.e.a.s. ef þú gerir push þá fer það þangað
- `git status` sjá status á hvaða branchi maður er og stöðuna á því (working dir).  Your branch is ahead of origin/master by 1 commit.  Þitt local branch is 1 commit.  Þýðir að þitt local branch er einu committi á undan master branchinu
- `git log` skoða commit sögu.
- `git log -p` skoða breytingarnar
- `git add filename` addar breyttri skrá á stage-ið
- `git reset HEAD filename` tekur breyttri skrá af stage-inu.
- `git checkout -b branchname`  checka út local sem nýtt branch.  Nú ef þú gertir git status `git status` þá kemur On branch branchname
- `git push origin master`pusha commitum á origin/master
- `git push -u origin minus`pusha minus branchi á origin -u upstream
- `git fetch origin GetPositionFromPlayer` Sækja bara branchið GetPositionFromPlayer.  Gott til að tékka á breytingum áður en pullrequesta er acceptuð

### Gera daglega
Þegar þú vinnur að breytingu eða fixi þá þarft þú að sjá til þess að þitt branch sé synkað við master branchið.
Þú mátt auðvitað gera það oftar en einu sinni á dag.
Það er hægt að gera með eftirfarandi skipunum.
```shell 
git checkout master
git pull
git checkout VIS-SOGUNR
git merge origin/master
#Keyrir svo öll Unit test til að athuga hvort allt sé OK
git push origin VIS-SOGUNR
```

## Gera pull request
Það þarf að pulla frá master, búa til branch gera breytingar og pusha svo branch-inu.  

Add og commit gerir þú auðvitað eftir TDD reglunum eins oft og þurfa þykir.
```
git pull
git checkout -b feturename
//gerum okkar breytingar
git add changefilename
git commit -m "made a beutiful and peasful changes to the file changefilename"
git push -u origin feturename
```
Að þessu loknu skal fara á github-repoinn og þar er hægt að smella á takkann "Compare & pull request"
Skrifa eitthvað subject og vitræna description. 

## You can pull changes from master to your branch
### Using fetch & pull
```shell 
git checkout my_branch         # move on your branch (make sure it exists)
git pull origin                # pull all changes
git pull origin master -no-ff  # pull changes from the origin remote, master branch and merge them into my_branch (no fast forward)
# If any changes pulled, check if code builds and unit tests succeed
git push my_branch             # push my_branch
```
### Using merge
```shell 
git checkout mybranch
git merge master (or rebase)
# After this you are directly pushing to your branch, before this just add and commit like this.
git add .
git commit -m "msg after merging"
git push origin mybranch
```
#ssh
To change beetwen two ssh files saved in config ssh -T bitbuc
f.example if host was bitbuc then this would change to that profile
we are talking about the file ~/.ssh/config


## Fleygja öllu og sækja nýtt
Henda öllum þínum breytingingum og sækja master aftur.
```
git reset --hard origin/master
git pull origin master
```


### Git glósur 2   ------------------

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
-     Commita oft
-     Gera mörg branches
-     Gera mörg master
-     Eitt aðalbranch (master)
-     Búa til branch fyrir alla fídusa
-     Gera merge master reglulega á branch-inu
-     Sérhvert branch getur innihaldið x-mörg commit
-     Commit-in eiga að vera lítil, litlar breytingar
-     Þegar búið er að útfæra fídusinn, er merge-að branch-ið inní master
-     Ekki óalgengt að henda svo branch-inu þegar það er búið að þjóna sínum tilgangi

 
 
http://git-scm.com/downloads
https://github.com/dthgs/project_Skjatexti
- 	git status - Hver er staðan á working directory
-  git checkout -b my-new-branch - Býr til nýtt branch
-  git checkout master - Skiptir yfir á master
-  git add . - Þannig að hægt sé að commit-a breytingum / Þannig að hægt sé að gera breytingar / "Næst þegar ég commit-a þá eiga þessar breytingar á þessum skrám að fara inn í commit-ið" / Setur skrárnar í 'Staging area' / Þessi breyting á að fara inn í næsta commit
-  git commit -m "Added some files" - Setur skrárnar í repository-ið, localt í hidden .git möppuna / Commenta commit-ið!
-  git push origin master - Sendir allar breytingar sem hafa verið gerðar á master
-  git clone git@github.com:danielbsig/TestApp.git - Klónar projectið / Tekur afrit af kóðanum / Býr til projectið inná GitHub
-  git merge master - Tekur inn breytingar á master, í branch-ið




