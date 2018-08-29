Git is a very useful tool. It gives us the ability to create repositories and use those repos to share and store information. Getting starting in Git can be a daunting and challenging.   
In this markdown file I will outline the basic workflow and the commands need to accomplish said workflow.  
- Obtaining a git repository  
  -  The most common way is cloning pre-existing repository to work on  
  -  You can do this using `git clone "some HTTPS from github"`  
- The next step is create your own branch to work from. We create a branch as to not disturb others work or to ruin stuff that already works.  
  -  To do this use the command `get branch develop`. This tells git to create a branch named developn  
    
After we make our own branch nothing we do on this branch will effect the main repo unless we tell it to.  
How do we tell the main branch to update?  
We will use 3 git commands to update the main repo.  
- `git add "whatever you want to add"`  
- `git commit -m "description of what you are adding"`  
- `git push origin develop`  

These command are extremely useful and you will use them constantly. `git add` adds whatever document you want to the commit list  
`git commit` commits the added documents and `git push` pushes them to the repo as a permanent change.  
That is the very basic navigation of git!  
