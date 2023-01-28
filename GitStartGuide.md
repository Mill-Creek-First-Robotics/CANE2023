# Git Start Guide

Git is the de facto version control tool for software development. It's used by nearly every program that is written because of it's versitality and light weight nature. Git is something that can be easy to pick up but hard to master. For now, we're not worried about mastering Git in any sense but just learning the basics that you would use in everyday tasks.

First, you need to install Git. That can be done [here](https://git-scm.com/). Download Git for whichever OS you use and run through the installer.

* When installing, choose defaults except for the "Configuring the Line Ending Conversions"
    * Choose the middle one "Checkout as-is, commit Unix-style line endings"
* After install, run GitBash and execute:  git config --global http.sslBackend schannel

Now, you are ready to deal with Git repositories, but first you need to clone a repository down locally. What this means is that Git stores the repository in a remote location (ie GitHub, Azure DevOps, GitLab, etc.) and cloning a Git repository creates a local repository on your computer. What this allows for is that you can commit work to your local repository without pushing it all up to the remote repository. So you can commit any work in progress stuff you have without affecting the remote repository at all. There are a multitude of ways to clone a repository, but I'm going to go over 2 ways, through the command line and through Visual Studio. There are applications that give you a GUI for git that you can use. the method of managing a git repository isn't relevant as long as good git practices are implemented.

## Cloning a Repository:

* Command Line
    * Go to where the git repository is stored (in this case Azure DevOps) and hit the clone button. From there, hit the copy button that is next to the text box. This is the link to the git repository that will be used in the command.
    * Open up your preferred command line tool (ie Mac/Linux Terminal, Windows Git Bash, Windows Command Prompt, etc.).
    * Navigate to the repository that you want the repository to be located locally.
    * Type in `git clone <link from step 1>`. Once that command finishes, you will have a local git repository.

* Visual Studio
    * From the startup screen, on the right side, click on a button that says `Clone a Repository`.
    * It should list `Azure DevOps` as a place you can browse for a repository. It will have you authenticate with Azure DevOps, but after that you should see a list of repositories. It will list both TFS repositories and Git repositories, so make sure you are choosing a Git one. Git's symbol an orange diamond with a branching line inside it.
    * In the textbox for Path, either type in the location you want to clone to locally, or browse your local files and choose a directory.
    * Hit Clone and it will clone the repository and should open it up in Visual Studio.

Now that you have a Git repository cloned down, it's time to learn how Git works and the commands you will use everyday. I would recommend supplementing this document with this [website](https://learngitbranching.js.org/) which is a great visualization tool for learning Git. It teaches everything from basic stuff like in this document to more advanced topics that will not be covered here. No matter how much you think you know about Git, there's probably more to learn.

A few commands that are very useful and/or necessary:

* `git status`
    * This tells you the status of your current repository, listing your current branch, what changes are in place, what changes are staged, and how many commits ahead/behind you are from the remote branch.
* `git pull`
    * This is how you update the current branch you are on with the latest code. Doing this will also pull the latest branches associated with the branch you pulled from.
* `git add <file-name>`
    * This stages a file to be committed so you can split up your changes into multiple commits
* `git commit -m <commit-message>`
    * This commits the staged files with whatever `commit-message` you supply
* `git push`
    * This will push your commit(s) to the upstream branch which is the remote branch associated with your local branch.
* `git reset`
    * I would recommend looking this command up because it's useful for deleting accidental commits among other things. But it can be dangerous if done improperly.
* `git merge <branch>`
    * This merges the `branch` you supply into the current branch you are on. This is useful for when someone made changes that you need in your branch. You should only need to merge the `main`/`master` branch into yours.

## Day to Day Workflow

On a day to day basis, these are following steps you should be taking while developing.

1. Create a branch off of `main`
2. Write some code
3. Stage your changes to your local branch
4. Commit your staged changes to your local branch
5. Once you satisfied with your work, push up your commits to the remote repository on a remote version of your branch
6. Repeat steps 2-5.
7. Once all your work has been committed up to the remote repo, make a pull request in Azure DevOps to merge your branch into main.

All these steps can be done through the command line or through a GUI like within Visual Studio.

Create a branch off `main`:

* Command Line:
    * Make sure you are on the `main` branch by running `git checkout main` from the root of the repository
    * Run `git checkout -b <branch-name>` and your local branch will be created. The `-b` argument is what tells git to make a new branch with that name and switch to that branch. Now you have created a new branch and have switched to that branch.

* Visual Studio:
    * In the bottom right of the screen, you should see the current branch name you are on (should be main if you have just cloned your repository). The symbol to look for a 3 circles with lines connecting them in a branching pattern. Clicking on should bring up a modal where you can manage all your branches.
    * Click on the `New Branch` button and type in the name of your branch in the first text box. The `Based On:` dropdown should be set to `main` so change it if it is not.
    * Make sure the `Checkout branch` box is checked so that VS switches to that branch after making it.

Now that you have a branch, you can do whatever you want to that branch without messing up `main` which is the source of truth for the application. `main` should also be what is deployed out to production (and if it isn't, it should be in the process of getting deployed to production).

Staging and Committing your work to your branch:

* Command Line
    * First, you need to stage your changes so that git knows what exactly to commit. To check what changes you have made, run `git status` which will tell you any files you have changed, any files you have added, and if there are any commits that can be pushed to the remote repo, and also what branch you are on. After that you need to run the `git add` command and supply a file path for which file to stage. This can be a regex string that will match the unstaged files and stage all matched files. If you accidently stage something you didn't want to stage, run `git restore --stage <file>`
    * Now you need to commit all the files you have staged. This is done by running `git commit -m <commit-message>`. This makes a commit to your local branch and repository. So far, you have not affected the remote repository.

* Visual Studio:
    * In the `View` tab on the top of the window, you should see a `Git Changes` line. If you do not, go to Team Explorer and hit the connect icon and select the Git repository you want to work with. The `Git Changes` should show up in the `View` tab.
    * In `Git Changes`, you should see a list of the files that were changed and added. You can click on each file to see exactly what was changed. To stage a file for committing, click the plus sign next to the file you want to stage. A staged files section should show up with all the staged files. You can unstage a file with the minus button next to the staged file.
    * Type your commit message in the text box at the top of `Git Changes` and click `Commit Staged`. This commits to your local branch and repo, not affecting the remote repository at all.

Pushing commits to remote branch:

* Command Line:
    * Once you have made all the commits you need/want to for the work your doing, you need to push your code up to the remote repository. The command is `git push origin <branch-name>`. If this is the first time you are pushing any changes to your branch, that branch won't exist in the remote repository. So you'll get an error saying there is no upstream branch to push to. To resolve this, the error will also print out the exact command you need to run. After running the command that prints out, all your code has been pushed up to a remote version of your branch.

* Visual Studio:
    * After committing, in the `Git Changes` window, you should see your branch name near the top with different arrow icons to the right of it. The push icon is the solid arrow pointing up with a line underneath it. It should be the exact middle icon. That's all you should need to do to push your commit(s) up to the remote repository.

## Pull Requests

A pull request (PR) is a code review that when approved and completed, will merge your branch into another branch. These are made after you have pushed all your changes to your branch and are satisfied with the work you've done. To make a PR in Azure DevOps, hover over the `Repos` tab on the left side (the orange icon) and click `Pull Requests`. Click `New Pull Request` in the top right corner and populate the left dropdown with your branch. So the top should say something like `<your-branch> into main`. Then fill out the title and description to let people know exactly what changes were made in this PR. You can add required reviewers which will make so that the PR cannot be completed until that person or those people have all approved the PR.

Once all approvals have been made, you can complete the PR with the `Complete` button in the top right. This will pop up with a panel with some options. I would recommend checking the box that mentions deleting your branch after merging. This is because your branch is essentially useless after a merge and if more changes need to be made, you should make a new branch entirely. So deleting the branches will keep the repository cleaner. Others have different opinions on this but this is what I prefer to do.