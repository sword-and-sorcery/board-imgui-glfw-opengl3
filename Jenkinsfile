def artifactory_name = "Artifactory Docker"
def artifactory_repo = "conan-local"
String docker_image = "conanio/gcc8"

node {
    docker.image(docker_image).inside('-v /tmp:/tmp --net=docker_jenkins_artifactory') {
        def server = Artifactory.server artifactory_name
        def client = Artifactory.newConanClient()
        def remoteName = client.remote.add server: server, repo: artifactory_repo

        stage("Get project") {
              checkout scm
        }

        stage("Get dependencies and create app") {
            client.run(command: "remote add inexorgame https://api.bintray.com/conan/inexorgame/inexor-conan")
            client.run(command: "install imgui/1.69@bincrafters/stable --build imgui")
            String createCommand = "create . sword/sorcery"
            client.run(command: createCommand)
        }

        stage("Upload packages") {
            String uploadCommand = "upload ui-board-imgui* --all -r ${remoteName} --confirm"
            def buildInfo = client.run(command: uploadCommand)
            //b.env.collect()
            server.publishBuildInfo buildInfo
        }
    }
}
