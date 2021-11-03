pipeline{
    agent any

    environment{
        REPO_NAME = 'HTTP_Messenger_Client'
        QMAKE_PATH = 'C:\\Qt\\6.1.2\\msvc2019_64\\bin\\qmake.exe'
        REQUIRED_FILES = 'C:\\Users\\akork\\Desktop\\HTTP_MESSANGER_CLIENT_REQUIRED_DLL_FILES'
        PROJECT_FOLDER_NAME = 'messenger'
        VISUAL_STUDIO_BAT_FILE = 'C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Auxiliary\\Build\\vcvars64.bat'
        NMAKE_PATH = 'C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Tools\\MSVC\\14.29.30133\\bin\\Hostx64\\x64\\nmake.exe'
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
                    bat "cd ${env.REPO_NAME}"
                    bat "cd ${env.PROJECT_FOLDER_NAME}"
                    bat "${QMAKE_PATH} -config debug"
                }
            }
        }
    }
    
    post{
        success{
            script{
                archiveArtifacts(
                    artifacts: "/${env.REPO_NAME}/*",
                    fingerprint: true
                )
            }
        }
    }
}
