Team rules and some tips:

- Prefered IDE is IntelliJ Idea Ultimate (You can get it for free if you are a student).
- Enable annotation process in project (We need it to use Lombok).
- Set tab size (and so on) to 2 because we want to have the same code style everywhere.
- Reformat code before commit (Ctrl + Alt + L).
- Be sure that Java 8 is enabled.
- Add .gitignore file to main project. Simple .gitignore file :

```
#!plain

.gitignore
.idea
.idea/
.classpath
.gradle/
.project
.settings/
bin/
build/

```

- Test your code and report bugs in Issues.
- Issue names : [Part_of_project][Technologies] Issue_Name

- Typical git workflow :

```
#!git

// Choose task from "Issues" and assign it to yourself. Mark it as open.
git branch -b IssueN
// Working
git add -A
git commit -m "Issue #N Resolved."

// Update state

git checkout master
git pull

// Rebase
git rebase master IssueN

// Resolve conflicts
git add -A
git rebase --continue

git push origin

// Create pull-request on bitbucket, mark task as resolved and add everyone to code-review.

```

Use Cherry-pick if you created branch with branch other than master!


```
#!git

git checkout -b IssueN
 
git add -A
git commit -m "Issue #N Resolved."

// add to bitbucket (eventually use -f)
git push origin IssueN
 
// update state

git checkout master
git pull
 
// delete your local branch
git branch -D IssueN
 
// create branch once again
git checkout -b IssueN
 
// git cherry-pick (copy commit hash from bitbucket)
git cherry-pick <hashag 1>
 
// resolve conflicts
git add -A
git commit
 
// repeat cherry-pick if you need

 ... 
 
// add code to bitbucket
git push origin IssueN -f
```



- Feel free to ask questions and propose own ideas!