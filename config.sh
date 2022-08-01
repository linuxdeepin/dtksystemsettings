#/usr/bin/bash
# -n name
# -h help

ChangeName() {
    echo "begin config name: $1..."
    name=$1
    sed -i "s/dtkdemo/${name}/g" .reuse/dep5
    # modify CMakeLists.txt
    sed -i "s/dtkdemo/${name}/g" CMakeLists.txt
    # rename config file
    sed -i "s/dtkdemo/${name^}/g" misc/dtkdemoConfig.cmake.in
    mv misc/dtkdemo.pc.in "misc/${name}.pc.in"
    mv misc/dtkdemoConfig.cmake.in "misc/${name}Config.cmake.in"
    # rename debian file
    mv debian/libdtkdemo.install "debian/lib${name}.install"
    mv debian/libdtkdemo-dev.install "debian/lib${name}-dev.install"
    # modify debian file content
    sed -i "s/dtkdemo/${name}/g" debian/{control,changelog,copyright}
    # modify test script
    sed -i "s/dtkdemo/${name}/g" test-recoverage.sh
    echo "end config name"
}

Print_help() {
    cat << EOF
config.sh <options> value

config the project for custom.

eg:./config.sh -n Test

Options:
  -n project name
  -h print help
EOF
}

while getopts ":n:a:h" optname
do
    case "$optname" in
      "n")
        ChangeName $OPTARG
        ;;
      "h")
        Print_help
        ;;
      ":")
        echo "No argument value for option $OPTARG"
        ;;
      "?")
        echo "Unknown option $OPTARG"
        ;;
      *)
        echo "Unknown error while processing options"
        ;;
    esac
    #echo "option index is $OPTIND"
done

if [ $# -eq 0 ];then
    Print_help
fi
