# Contributing Guidelines

Zapdos is a collaborative software project, and we welcome all contributions!
Because we have multiple developers and customers working on and using the code,
we have various standards, procedures, and testing processes to maintain the
quality of Zapdos code. Below, we'll outline various things to keep in mind when
developing Zapdos and submitting code.

## Getting started with an idea? Start a Discussion!

!style halign=left
When getting started with a new idea for new capabilities, enhancements, or
bugfixes on Zapdos, it's worth your time to start a discussion with the current
Zapdos community. Other community members can often lend ideas on
implementation and approaches to the work that might improve the quality of the
final result. They also might be able to tell you if something is already possible
in the current code version. Check out
[the Zapdos Discussion Forum](https://github.com/shannon-lab/zapdos/discussions)
to start a conversation!

## Follow the code standards

!style halign=left
When modifying Zapdos code, it is requested that the [code_standards.md] are
followed. These guidelines make sure that code in the repository follows a
consistent look and feel for ease of current and future development.

## Referencing Issues

!style halign=left
It is recommended that any new Zapdos modifications reference a Zapdos
[Issue](https://guides.github.com/features/issues/) number. This is not required
to make a [Pull Request (PR)](https://guides.github.com/activities/forking/#making-a-pull-request),
but helps in the review process (to give context to new or modified code). In a
PR or git commit message, referencing an issue is as easy as adding `refs #<number>`,
where `<number>` is an active Zapdos issue. Issues can also automatically be
closed by PRs by adding `closes #<number>` in the body of the PR.

## Work in a GitHub fork

!style halign=left
Zapdos development follows a "Fork & Pull" development process. See more
information on [repo forking on GitHub](https://guides.github.com/activities/forking/).

### 1. Fork Zapdos and clone

!style halign=left
- Navigate to [https://github.com/shannon-lab/zapdos](https://github.com/shannon-lab/zapdos)
- Click the "Fork" button near the upper right corner of the page.
- Clone your new fork to your local machine using the following command:

```
git clone https://github.com/<your_user_name>/zapdos.git
```

### 2. Add an `upstream` git remote

!style halign=left
Add the main Zapdos repository as an "upstream" git remote (so that you can
[fetch](https://git-scm.com/docs/git-fetch) updates and code changes from the
main repository):

```
cd ~/projects/zapdos
git remote add upstream https://github.com/shannon-lab/zapdos.git
```

To fetch changes, run:

```
git fetch upstream
```

### 3. Make modifications

!style halign=left
Create branch for your work:

```
git checkout -b branch_name upstream/devel
```

Then make any modifications and commit them:

```
git add new_code.h new_code.C
git commit -m "Add some awesome changes (Refs #1234)"
```

If you've been working for some time on this new code, it is possible that some
Zapdos updates have occurred in the meantime. It is recommended that you
[rebase](https://git-scm.com/book/en/v2/Git-Branching-Rebasing) your changes on
top of the current code in the Zapdos "devel" branch.

```
git fetch upstream
git rebase upstream/devel
```

### 4. Push modifications up to your fork

!style halign=left
Push your branch into your fork on GitHub:

```
git push origin branch_name
```

## Create a Pull Request

!style halign=left
Returning to the [main Zapdos repo page](https://github.com/shannon-lab/zapdos),
you can create a [pull request](https://guides.github.com/activities/forking/#making-a-pull-request)
to submit your modifications to the Zapdos code base.

## Reach out to a member of the Zapdos development team

!style halign=left
Usually, a member of the Zapdos development team will reach out to review or
start testing on your pull request. If not, please tag (using the `@<user-name>`
GitHub syntax) one of them in the pull request discussion.

## Testing, review, and merging

!style halign=left
Once a pull request is submitted it usually undergoes automated testing, but
it might have to be manually started by a member of the development team (if a
first time contributor). Then a formal review of the code is performed, and the
assigned development team member will give comments and code change suggestions.
Once all concerns with the code modifications have been resolved and testing
has all passed successfully, the approving team member can merge the code into
Zapdos.
