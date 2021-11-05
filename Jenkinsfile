pipeline{
    agent any

    environment{
        REPO_NAME = 'HTTP_Messenger_Client'
        // QMAKE_PATH = 'C:\\Qt\\6.1.2\\msvc2019_64\\bin\\qmake.exe'
        // REQUIRED_FILES = 'C:\\Users\\akork\\Desktop\\HTTP_MESSANGER_CLIENT_REQUIRED_DLL_FILES'
        PROJECT_FOLDER_NAME = 'messenger'
        // VISUAL_STUDIO_BAT_FILE = '"C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Auxiliary\\Build\\vcvars32.bat"'
        // NMAKE_PATH = '"C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Tools\\MSVC\\14.29.30133\\bin\\Hostx64\\x64\\nmake.exe"'
        ISCC = '"C:\\Users\\akork\\Desktop\\InnoSetupPortable\\App\\Inno Setup\\iscc"'
    }

    stages{
        stage('Preparing the directory'){
            steps{
                dir(env.REPO_NAME){
                    bat "echo '======================CHECKOUTING========================='"
                    cleanWs()
                    checkout scm
                }
            }
        }
        stage('Building the .pro file with QT'){
            steps{
                dir(env.REPO_NAME){
                    bat "echo '======================BUILDING THE PRIOJECT========================='"
                    dir(env.PROJECT_FOLDER_NAME){
                          bat ' .\\qtbuild.bat'

                    }
                }
            }
        }
        stage('Generating installer'){
            steps{
                bat "echo '======================GENERATING INSTALLER========================='"
                bat "${env.ISCC} installer_script.iss"
            }
        }
    }
    
    post{
        success{
            script{
                archiveArtifacts(
                    artifacts: "${env.REPO_NAME}\\Output\\HTTP_Messenger_installer.exe",
                    fingerprint: true
                )
            }
        }
    }
}