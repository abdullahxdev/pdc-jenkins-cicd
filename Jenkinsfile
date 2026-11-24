pipeline {
    agent any

    stages {
        stage('Checkout') {
            steps {
                checkout scm
                sh 'git log -1 --pretty="Commit %h by %an: %s"'
            }
        }
        stage('Build') {
            steps {
                sh 'gcc --version | head -1'
                sh 'mkdir -p build && gcc -fopenmp -O2 -o build/parallel_sum parallel_sum.c'
            }
        }
        stage('Test') {
            steps {
                sh './build/parallel_sum --test'
            }
        }
        stage('Run') {
            steps {
                sh 'hostname; nproc'
                sh './build/parallel_sum | tee build/run_output.txt'
            }
        }
    }

    post {
        success {
            archiveArtifacts artifacts: 'build/run_output.txt'
            echo 'Pipeline finished: build, test and parallel run all passed.'
        }
        failure {
            echo 'Pipeline failed. Check the stage logs above.'
        }
    }
}
