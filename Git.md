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
- `git log --graph` Skoða branch tree
- `gitk` Opna gui sem sýnir branch tree
- `git status` sjá status á hvaða branchi maður er og stöðuna á því (working dir).  Your branch is ahead of origin/master by 1 commit.  Þitt local branch is 1 commit.  Þýðir að þitt local branch er einu committi á undan master branchinu
- `git log` skoða commit sögu.
- `git log -p` skoða breytingarnar
- `git log origin/dev..HEAD` Listar þetta öll un-pushed commit á dev. (Þ.e.a.s ef þú ert á dev branch-i)
- `git reflog show --no-abbrev <branch-name>` Finna sögu og frá hvaða commiti branch er búið til
- `git remote` skoða hvaða remote þú ert tengdur.. þ.e.a.s. ef þú gerir push þá fer það þangað
- `git add filename` addar breyttri skrá á stage-ið
- `git clean -f` Remove untracked files from the working tree
- `git reset HEAD filename` tekur breyttri skrá af stage-inu.
- `git reset --hard origin/master` Hendir öllu á current branch og gerir það eins og master branch (lætur head benda á sama stað og master branch gerir)
- `git checkout -b branchname`  checka út local sem nýtt branch.  Nú ef þú gertir git status `git status` þá kemur On branch branchname
- `git checkout -b myFeature dev`  búa til og checkout nýtt branch local branch út frá dev branchi
- `git branch -d <local-branch>` Eyða local branchi 
- `git push origin --delete <remote-branch-name>` Eyða remote branch **Hættulegt**
- `git push origin master`pusha commitum á origin/master
- `git push -u origin minus`pusha minus branchi á origin -u upstream
- `git fetch origin GetPositionFromPlayer` Sækja bara branchið GetPositionFromPlayer.  Gott til að tékka á breytingum áður en pullrequesta er acceptuð
 
-  `git clone git@github.com:danielbsig/TestApp.git - Klónar projectið / Tekur afrit af kóðanum / Býr til projectið inná GitHub
-  `git merge master - Tekur inn breytingar á master, í branch-ið

[Hér á ég líka glósur git process á öðru projecti](https://github.com/guttih/react/blob/master/gitProcess.md)

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

## Svissa á milli brancha
Þegar þú ert með breytingar í einu branchi, en villt ekki tékka þær inn áður en þú svissar þá getur þú stashað breytingunum.
Þú hoppar yfir í git Bash
gefur eftirfarandi skipun sem er stytting fyrir `git stash push`
```
git stash
```
Svissar svo yfir á nýja branchið og vinnur í því.
Þegar því hefur svo klárað vinnu í nýja branchinu og villt svissa aftur til baka, þá ferð þú aftur yfir á upphaflega branchið og gefur skipunina 
```
git stash pop
```
## Breyta gömlum commit texta (Amending commit message)
Hægt er að breyta commit message á gömlu commiti. Textaleitaðu á [þessari síðu](https://help.github.com/articles/changing-a-commit-message/#commit-has-not-been-pushed-online) að "Amending the message of older or multiple commit messages"


## You can pull changes from master to your branch

### Using rebase
Vera staddur á þínu branchi og sækja main inn í það, en gera þín commit þau nýjustu
```shell 
git checkout mybranch
git pull origin main -r
#Skoða hvaða commit eru nýjust (þín eiga að vera nýjust), getur appendað tölu param til að fá að vita hve mikið þú vilt sjá
git log --oneline 

# Ef þú ert beðinn um að pulla, ekki gera það því þá fer historyan í rugl.  notaðu -f rofann þegar þú pushar
# Þegar þú pushar á branchið þitt þá þarftu að nota -f (force) því annars færðu miljón reviewers á kóða sem breyttist bara á main (en ekki bara þínu branchi)
git push -f origin mybranch

# svo getur þú bara haldið áfram á branchinu þínu eins og venjulega
git add .
git commit -m "msg after merging"
git push origin mybranch
```
#### Using rebase conflicts
Þegar það er conflict á einhverjum skrám eftir að þú gefur skipunina `git pull origin main -r` þá þarft þú að resolva það conflict, adda skránum aftur og gefa svo skipunina ` git rebase --continue`  þegar það er búið, þá getur þú pushað svona: `git push -f origin mybranch`. 

ps. Þegar þú ert að rebasea þá býr git til temorary rebase branch og í þessu tilviki þá ertu að vinna á því

```shell 
git checkout mybranch
git pull origin main -r
# Let's say you got some files which are in conflict
# Open text editor and resolve the conflicts

# add all files (which were in conflict)
git add .

# give next command, and accept the default text by exiting the editor (for me its vim and exit key comination is ':x' and press 'return'
git rebase --continue

#now you can push and to keep the history correct use -f
git push -f origin mybranch

```

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

## Hreinsa burtu skrár sem ætti að .gitignor - a
 - `git clean -xdn` Sýna lista yfir skrár sem hreinsun myndi eyða
 - `git clean -xdf` Framkvæma hreinsun / eyða skrám

## Close issue with commit message
 - Syntax `KEYWORD #ISSUE-NUMBER`
 - Keywords: `close`, `closes`, `closed`, `fix`, `fixes`, `fixed`, `resolve`, `resolves`, `resolved`.
 
| Linked issue                    | Syntax                                | Example                                                      |
|:--------------------------------|:--------------------------------------|:-------------------------------------------------------------|
| Issue in the same repository    | KEYWORD #ISSUE-NUMBER                 | Closes #10                                                   |
| Issue in a different repository | KEYWORD OWNER/REPOSITORY#ISSUE-NUMBER | Fixes octo-org/octo-repo#100                                 |
| Multiple issues                 | Use full syntax for each issue        | Resolves #10, resolves #123, resolves octo-org/octo-repo#100 |
|                                 | 	                                     |                                                              |


 [documentation](https://docs.github.com/en/github/managing-your-work-on-github/linking-a-pull-request-to-an-issue#linking-a-pull-request-to-an-issue-using-a-keyword)

## hooks
Með því að breyta skrá með ákveðnu skráarnafni í möppunni `.git/hooks` þá má gera sjálfvirkni við ákveðna git aðgerðir.

### prepare-commit-msg
#### Setja málsnúmer fremst í branch nafni fremst í öll commit messages
Ef branch byrjar á málsnúmeri og eftir málsnúmerið þá er sett bandstrik "-" þá mun þessi scripta(hook) afrita málsnúmerið og setja í upphaf á hverju commit message þegar þú pushar því.
```
#!/bin/sh
# Include any branches for which you wish to disable this script
if [ -z "$BRANCHES_TO_SKIP" ]; then
  BRANCHES_TO_SKIP=(master develop staging test)
fi
# Get the current branch name and check if it is excluded
BRANCH_NAME=$(git symbolic-ref --short HEAD)
BRANCH_EXCLUDED=$(printf "%s\n" "${BRANCHES_TO_SKIP[@]}" | grep -c "^$BRANCH_NAME$")
# Trim it down to get the parts we're interested in
TRIMMED=$(echo $BRANCH_NAME | sed -e 's:^\([^-]*-[^-]*\)-.*:\1:' -e \
    'y/abcdefghijklmnopqrstuvwxyz/ABCDEFGHIJKLMNOPQRSTUVWXYZ/')
# If it isn't excluded, preprend the trimmed branch identifier to the given message
if [ -n "$BRANCH_NAME" ] &&  ! [[ $BRANCH_EXCLUDED -eq 1 ]]; then
  sed -i.bak -e "1s/^/$TRIMMED /" $1
fi
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
 

 





