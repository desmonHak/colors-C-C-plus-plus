@echo off

git add .
git config advice.addIgnoredFile false
git add -f .gitignore
echo code.sh >> .gitignore

git add -f code.sh
git rm --cached "./code.sh"

set OLD_EMAIL=anon2123234343441@gmail.com
set NEW_EMAIL=aaa@gmail.com
set NEW_NAME=Desmon

git status
git config --global user.name "%NEW_NAME%"
git config --global user.email "%NEW_EMAIL%"
git commit -m "confirmacion"

git filter-branch --index-filter "git rm --cached --ignore-unmatch code.sh" HEAD

git filter-repo --mailmap "%OLD_EMAIL% = %NEW_NAME% <%NEW_EMAIL%> %OLD_EMAIL% = %NEW_NAME% <%NEW_EMAIL%>" --force

echo subiendo cambios
git config --global credential.helper cache

git push --force --all
git push --force --tags
git log
