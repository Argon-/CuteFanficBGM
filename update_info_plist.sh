set -e

# latest git tag
VER=$(git describe --abbrev=0 --tags | tr -d v)

plutil -replace CFBundleVersion -string "${VER}" template_Info.plist
plutil -replace CFBundleVersion -string "${VER}" CuteFanficBGM.app/Contents/Info.plist
plutil -replace CFBundleShortVersionString -string "${VER}" template_Info.plist
plutil -replace CFBundleShortVersionString -string "${VER}" CuteFanficBGM.app/Contents/Info.plist
echo "Set version to: ${VER}"
