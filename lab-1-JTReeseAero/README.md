# Lab Assignment 1
# An introduction to basic tools for modern engineering

| Assignment Dates | |
| --- | --- |
|**Assigned on**: | Jan. 9, 2018 |
|**Due on**: | Jan. 19, 2018 |
|**Accepted on**: | |


## Grading Rubric

|Deliverable | Points Awarded | Maximum Points |
|---|---|---|
| Basic Branch | | 5 |
| Grok Git | | 5 |
| Master Markdown | | 5 |
| Learn LaTeX | | 5 |
| Total Score | | 20 |
| Slip days used | | |


## Introduction

In this assignment you will prepare the necessary resources for interfacing with the class and completing assignments.  For this assignment you will complete tutorials and achieve basic proficiency with three main tools:

1. Git
2. Markdown
3. LaTeX

You've already started this assignment by accepting the link you received through Github classroom!  Your next step will be to create a branch of this assignment.  **Always create a branch as a first step!** Creating a branch is one of the most essential best practices for working in a repository.  It lets you easily collaborate with larger groups, organize your work, and work in isolation.

**develop**: It is standard practice to do active development on a branch called "develop", as follows:

    git branch develop
    git checkout develop
    git push origin develop

This creates a new branch from your current working branch, switches to that branch, and then pushes the new branch to the remote repository (GitHub).

To save your changes, always make sure you are on your development branch:

    git checkout develop

    <work on your assignment>

    git add <new or changed files>
    git commit -m "A descriptive note of what you changed"
    git push origin develop

The time and date of your pull request from develop into master will determine your submission time. See the lab manual for details.


## Grokking Git

Git is a version control system used for tracking changes and coordinating work on digital files among multiple people. Version control, or revision/source control is a way to manage changes on documents, code, or other data to allow  concurrent editing, resolution of conflicts, and long-term management and saving of changes.  You can read more about why using revision control in higher education is important for your future [here](https://jarofgreen.co.uk/2013/05/why-programmers-should-learn-git/).

- [x] Complete the
  [Git 101 Tutorial](https://try.github.io/levels/1/challenges/1) -
  this should take about 15 minutes.
- [x] Review the Github
  [cheat sheet](https://education.github.com/git-cheat-sheet-education.pdf)
  which will help you remember key commands and workflows with Git.
- [x] Make note of the additional resources available
  [here](https://help.github.com/articles/good-resources-for-learning-git-and-github/)
  for going deeper into your learning about git and Github.


## Mastering Markdown

Since we will be using git for all assignments in this class, it will be important for you to learn **Markdown**.  Markdown is a lightweight language for formatting text that is designed to be more human readable than most markup languages, like HTML, but also to be easily rendered in HTML, or rich text display formats.  Markdown is the preferred language of git readme files, and is the language used to code the file you are reading.

- [x] Read the *Mastering Markdown* guide available
  [here](https://guides.github.com/features/mastering-markdown/).
- [x] In your assignment repository, make sure you mark the boxes for completed objectives, and commit the changes to git!

Markdown was originally developed by John Gruber of [Daring Fireball](daringfireball.net), he's written about markdown [here](http://daringfireball.net/projects/markdown/).

- [x] Create a new directory for a markdown assignment called "markdown", and create a basic markdown file in it named "git.md".  Include a short discussion of the git workflow, with separate sections for git, and the importance of good documentation.  Include git commands formatted as code/syntax to show the basics of the git workflow.


## Learn LaTeX

While Markdown is great for README files, and for general communication and notation, it really fails when it comes to mathematics, and other important science and technology communication related topics, like graphs and figures.  Lucky for us, there is LaTeX.  LaTeX is a document preparation system designed to allow users to write up scientific and mathematical results easily, quickly, and in a format-agnostic manner that can be templated, styled, and modified without changing the text itself.  This makes it different from word processors like LibreOffice, MS Word, or Google Docs in which formatting information is explicitly set in the text.

For this last part of Lab 1, you will make modifications to a LaTeX report, and compile a final PDF of your assignment for submission.

- [x] Bookmark the 
  [wikibook](https://en.wikibooks.org/wiki/LaTeX) 
  on LaTeX, it answers any question you are likely to have, including very advanced ones.  Don't try and read the whole thing today, it's very long!
- [x] Bookmark the LaTeX 
  [cheat sheet](http://www.ctan.org/tex-archive/info/latexcheat/latexcheat/latexsheet.pdf), 
  it will come in handy!

In the report directory is a main.tex file. Use this as the starting point for your LaTeX report this week as directed below.


- [x] Skim the [basics](https://en.wikibooks.org/wiki/LaTeX/Basics) section of the LaTeX wikibook without following their directions get a taste for LaTeX syntax.

- [x] Modify the section marked in the main.tex file in the report directory (see lab manual).

- [x] Compile your new document as a PDF (see the lab manual for assistance).
- [x] Commit the changed file to your repository.  Make sure to push your changes!

When you have completed every task with a check-box above, make sure all your work is committed to git and pushed to GitHub. All that is left is to make a pull request from develop onto master.
