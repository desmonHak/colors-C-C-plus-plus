@echo off

git add .
git config advice.addIgnoredFile false
git add -f .gitignore
echo . >> .gitignore
echo code.bat >> .gitignore

git add -f code.sh
git rm --cached "./code.sh"

set OLD_EMAIL=anon2123234343441@gmail.com
set NEW_EMAIL=aaa@gmail.com
set NEW_NAME=Desmon

git status
git config --global user.name "%NEW_NAME%"
git config --global user.email "%NEW_EMAIL%"
git commit -m "confirmacion"

git filter-repo --path code.sh --invert-paths
rem git filter-branch --index-filter "git rm --cached --ignore-unmatch code.sh" HEAD

git filter-branch -f --env-filter "
  if ""%GIT_AUTHOR_EMAIL%"" == ""%OLD_EMAIL%"" (
    set FOUND_AUTHOR_EMAIL=1
  )
  if ""%GIT_COMMITTER_EMAIL%"" == ""%OLD_EMAIL%"" (
    set FOUND_COMMITTER_EMAIL=1
  )

  if defined FOUND_AUTHOR_EMAIL (
    set GIT_AUTHOR_EMAIL=%NEW_EMAIL%
    set GIT_AUTHOR_NAME=%NEW_NAME%
  )
  if defined FOUND_COMMITTER_EMAIL (
    set GIT_COMMITTER_EMAIL=%NEW_EMAIL%
    set GIT_COMMITTER_NAME=%NEW_NAME%
  )
" -- --all

echo subiendo cambios
git config --global credential.helper cache

git push --force --all
git push --force --tags
git log
