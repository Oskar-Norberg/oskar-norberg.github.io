---
title: Custom Unity Packages
date: 2025-02-17 00:00:00 +01:00
tags: [Unity Packages, Unity, UI, Behaviour Trees]
description: A journal entry detailing my experience in game project 2
image: "/assets/img/postHeaders/customUnityPackage.png"
---

Game Project 1 Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum. [INSERT LINK HERE](https://futuregames.itch.io/lizardescape).

<hr>

All the services are free, source code the site was placed on my [github](https://github.com/piharpi/mahendrata.now.sh) repository and intergration with ~~[netlify](https://netlify.com)~~ service, another service that you can use is [github page](https://pages.github.com/) for hosting your own static site.

<hr>

#### Let's do this

So, before we start create a site, you need some tools, you can self paced for how to installing each tools, on this guide i'm just want to show you how to install jekyll and deploying in netlify, but make sure you have each tools below.

#### Prerequisites

Requirements before we doing magic show.

- [Ruby](https://www.ruby-lang.org/en/downloads/) programming language
- [Git](https://git-scm.com) (version control)
- [Netlify](https://netlify.com) and [Github](https://github.com) account
- [Bundler](https://bundler.io)

#### Installation

First, you need some [SSG](https://www.staticgen.com/), there are many kind ssg, but in case i'm using Jekyll cause i'm already familiar with it, open your terminal and type command on below

```bash
$ bundle install jekyll # installing jekyll in your machine
$ jekyll new my-site && cd my-site # create new jekyll project
$ jekyll s # run jekyll server
```

Now, jekyll is running on your local machine, open your browser and go to `localhost:4000` is default address from jekyll, press <kbd>CTRL</kbd> + <kbd>C</kbd> to stop the jekyll server.

#### Adding remote repository

Before we adding remote repository, you must have [github](https://github.com/new) repository, if already have repository, just add github remote address to your local folder, with the following commands

```bash
$ git init # initializing project folder
$ git remote add origin https://github.com/YOUR-USERNAME/YOUR-REPO.git # change UPPERCASE with your own!
$ git add -A && git commit -m "Initialize" && git push -u origin master # push code to github
```

Now check your github repository, make sure the files is uploaded correctly.

#### Deploying to netlify

Go [netlify](https://netlify.com) dashboard, and following this step.

1. click `new site from git`, then choose `Github`.
2. then choose your repository where is the jekyll sources uploaded.
3. netlify smart enough to configuring, we just need's are hosting's are hosting's are hosting's are hosting to click `Deploy site button`.

Wait for moment, and voila..! your site's are hosting and using `.netlify.com` tld, if your website wants to look professional, just buy a domain from your favorite domain store. or if you the first time, I advice using namecheap.com*(isn't sponsor)* \*based on my experienced it provides good service and have various TLDs.

So, what you waiting for, just create your own website for free.
