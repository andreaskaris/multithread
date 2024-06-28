IMAGE ?= quay.io/akaris/threads

.PHONY: build-fork
build-fork:
	gcc -o _output/fork fork.c

.PHONY: build-thread
build-thread:
	gcc -o _output/thread thread.c

.PHONY: build
build: clean build-fork build-thread

.PHONY: clean
clean:
	rm -f _output/*

.PHONY: container-build
container-build:
	podman build -t $(IMAGE) .

.PHONY: container-push
container-push:
	podman push $(IMAGE)

.PHONY: deploy
deploy:
	oc apply -f pod.yaml

.PHONY: undeploy
undeploy:
	oc delete -f pod.yaml