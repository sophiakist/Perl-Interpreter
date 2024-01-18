# Language Interpreter Lab

The project has been set up for Java and Gitlab CI.
You must add your language definitions to the _docs_ folder.
You will find all the source code in _src_ folder.
The Java JUnit test will be automatically run when you commit to Gitlab.

## Forking the Repository

To create a fork of this repository, click on the *fork* button on the original repository at <https://gitlab.cs.wallawalla.edu/cptr354/language-interpreter-lab>.
Copy the URL of your forked repository by clicking the clipboard icon next to it.
The URL should look something like:

```shell
git@gitlab.cs.wallawalla.edu:YourUsername/language-interpreter-lab.git
```

Once you have forked the repository, you must set its visibility level to private so that only you can see it.
To do this,

1. Click on the gear icon at the top right of the project page in GitLab.
2. Select *Edit Project* from the drop-down menu.
3. Set the *Visibility Level* to *Private* in the *Project settings* box.
4. Scroll down until you find the green *Save changes* button and click it.

Add your partner to the project.
From the project homepage:

1. Click on the side menu labeled *Members*.
2. Search for your partner.
3. Give them *Maintainer* access to the project.

## Setting Up Your Local Workspace

Create your local workspace by cloning the repository to your machine.
Put the repository in a place will remember.
You can clone the repository by using a command similar to this:

```shell
git clone git@gitlab.cs.wallawalla.edu:YourUsername/language-interpreter-lab.git
```

If you are asked to enter a password, you need to set up your ssh key.

```shell
ssh-keygen
more ~/.ssh/id_rsa.pub
```

Copy the generated public key in to GitLab under your profile ssh keys

Finally, to make sure that you can receive updates easily (see below), type the
following commands in the command window at the bottom of the Cloud 9 screen.

```shell
git remote add upstream git@gitlab.cs.wallawalla.edu:cptr354/language-interpreter-lab.git
```

## Passing Tests

Every time you commit code and push it to gitlab, the test will be automatically executed.
You can find the results by look at the **CI/CD** menu option.
It will list the recent jobs executed and show there status.
You can find the details of each job by clicking on them.
