pipeline {
    agent any
    environment {
        // Set the ssh key for the mirror using secret private key
        PRIVATE_KEY = credentials('EPITECH_SSH_KEY')
        PUBLIC_KEY = credentials('EPITECH_SSH_PUBKEY')
        MIRROR_URL = 'git@github.com:EpitechPromo2027/B-CCP-400-NAN-4-1-theplazza-quentin.tennerel.git'
    }
    stages {
        stage('📥 Checkout') {
            steps {
                // Clean before checkout
                cleanWs()

                // Clone the repository
                checkout scm
            }
        }
        stage('🕵️ Lint') {
            steps {
                // Run docker container
                sh 'docker run --rm --security-opt "label:disable" -v "$(pwd)":"/mnt/delivery" -v "$(pwd)":"/mnt/reports" ghcr.io/epitech/coding-style-checker:latest "/mnt/delivery" "/mnt/reports"'

                // Parse the report and fail the build if the quality gate is not passed
                script {
                    def report = readFile 'coding-style-reports.log'
                    def errors = report.readLines()
                    for (error in errors) {
                        def file = error.split(':')[0]
                        def line = error.split(':')[1]
                        def type = error.split(':')[2]
                        def code = error.split(':')[3]
                        unstable "File: ${file}, Line: ${line}, Type: ${type}, Code: ${code}"
                    }
                    // Archive the report
                    archiveArtifacts 'coding-style-reports.log'

                    // Publish the report
                    publishHTML([allowMissing: false, alwaysLinkToLastBuild: false, keepAll: true, reportDir: '.', reportFiles: 'coding-style-reports.log', reportName: 'Coding Style Report', reportTitles: ''])

                    // Fail the build if the quality gate is not passed
                    if (errors.size() > 0) {
                        // If on main branch, fail the build otherwise just warn
                        if (env.BRANCH_NAME == 'main') {
                            error "Too many coding style errors"
                        }
                        else {
                            unstable "Too many coding style errors"
                        }
                    }
                }
            }
        }
        stage('🏗️ Build') {
            agent {
                docker {
                    image 'epitechcontent/epitest-docker:latest'
                    args '-v /var/run/docker.sock:/var/run/docker.sock'
                }
            }
            steps {
                ansiColor('xterm') {
                    // Clean before building
                    sh 'make fclean'

                    // Run the build
                    sh 'make'

                    // Check file presence (e.g. binary, library, etc.)
                    script {
                        def BIN_NAMES = ['plazza']

                        for (BIN_NAME in BIN_NAMES) {
                            if (!fileExists(BIN_NAME)) {
                                error "The binary file ${BIN_NAME} does not exist"
                            } else {
                                echo "The binary file ${BIN_NAME} exists"
                                archiveArtifacts artifacts: "${BIN_NAME}", fingerprint: true
                            }
                        }
                    }
                }
            }
        }
        stage ('🧪 Tests') {
            agent {
                docker {
                    image 'epitechcontent/epitest-docker:latest'
                    args '-v /var/run/docker.sock:/var/run/docker.sock'
                }
            }
            steps {
                // Run the tests
                sh 'make tests_run'

                script {
                    def dirs = []

                    for (_dir in dirs) {
                        junit(testResults: "${_dir}/criterion.xml", allowEmptyResults : true)

                        dir(_dir) {
                            sh "gcovr --cobertura cobertura.xml --exclude tests/ --exclude libs/"
                            def coverage_id = _dir.replaceAll('/', '-') + "-coverage"

                            recordCoverage(tools: [[parser: 'COBERTURA']], sourceDirectories: [[path: "${_dir}/**"]],
                                id: coverage_id, name: "${_dir} Coverage",
                                sourceCodeRetention: 'EVERY_BUILD')
                        }
                    }
                    junit(testResults: "criterion.xml", allowEmptyResults : true)
                }

                sh 'gcovr --cobertura cobertura.xml --exclude tests/ --exclude libs/'

                recordCoverage(tools: [[parser: 'COBERTURA']],
                    id: "coverage", name: "Coverage",
                    sourceCodeRetention: 'EVERY_BUILD')
            }
        }
        stage('🪞 Mirror') {
            when {
                branch 'main'
            }
            steps {
                // Remove the mirror if it already exists
                sh "git remote remove mirror || true"

                // Add the mirror
                sh "git remote add mirror ${MIRROR_URL}"


                // Switch to the main branch
                sh "git checkout main"

                // Setup the ssh key for the mirror
                withCredentials([sshUserPrivateKey(credentialsId: 'EPITECH_SSH_KEY', keyFileVariable: 'PRIVATE_KEY')]) {
                    sh 'GIT_SSH_COMMAND="ssh -i $PRIVATE_KEY" git push --mirror mirror'
                }
            }
        }
    }
    post {
        // Clean after build
        always {
            cleanWs(cleanWhenNotBuilt: true,
                    deleteDirs: true,
                    disableDeferredWipeout: true,
                    notFailBuild: true,
                    patterns: [[pattern: '.gitignore', type: 'INCLUDE'],
                               [pattern: '.propsfile', type: 'EXCLUDE']])
            sh 'make fclean'
        }
    }
}
