pipeline{
    agent any

    environment{
        REPO_NAME = 'HTTP_Messenger_Client'
        QMAKE_PATH = 'C:\\Qt\\6.1.3\\mingw81_64\\bin\\qmake.exe'
        REQUIRED_FILES = 'C:\\Users\\нободи\\Desktop\\HTTP_MESSENGER_CLIENT_DLLS'
        VISUAL_STUDIO_BAT_FILE = 'C:\\Program Files\\Microsoft Visual Studio\\2022\\Preview\\VC\\Auxiliary\\Build\\vcvars64.bat'
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
        stage('Building the project'){
            steps{
                dir(env.REPO_NAME){
                    bat "echo '======================BUILDING THE PRIOJECT========================='"
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
