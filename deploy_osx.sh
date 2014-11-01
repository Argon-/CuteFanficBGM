set -e

BUNDLE_NAME="CuteFanficBGM.app"
DIR_NAME="CuteFanficBGM"



$(brew --prefix qt5)/bin/qmake
make -j8

mkdir -p "${DIR_NAME}"
cp -r "${BUNDLE_NAME}" "${DIR_NAME}/"
$(brew --prefix qt5)/bin/macdeployqt "${DIR_NAME}/${BUNDLE_NAME}"

cp "Sisterhood.txt" "${DIR_NAME}"
cp "Songlist.txt" "${DIR_NAME}"
cp "LICENSE" "${DIR_NAME}"
find "${DIR_NAME}/" -name ".DS_Store" -type f -exec rm {} \;
zip -r "${DIR_NAME}_mac.zip" "${DIR_NAME}"
rm -rf "${DIR_NAME}"
