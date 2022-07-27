#/usr/bin/bash
# -n name
# -h help

ChangeName() {
    echo "begin config name: $1..."
    name=$1
    sed -i "s/dframework/${name}/g" .reuse/dep5
    # modify CMakeLists.txt
    sed -i "s/dframework/${name}/g" CMakeLists.txt
    # rename config file
    sed -i "s/dframework/${name^}/g" misc/dframeworkConfig.cmake.in
    mv misc/dframework.pc.in "misc/${name}.pc.in"
    mv misc/dframeworkConfig.cmake.in "misc/${name}Config.cmake.in"
    # rename debian file
    mv debian/libdframework.install "debian/lib${name}.install"
    mv debian/libdframework-dev.install "debian/lib${name}-dev.install"
    # modify debian file content
    sed -i "s/dframework/${name}/g" debian/{control,changelog,copyright}
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
