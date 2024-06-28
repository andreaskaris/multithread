FROM registry.fedoraproject.org/fedora as builder
WORKDIR /apps
COPY . .
RUN yum install -y gcc make
RUN make build

FROM registry.fedoraproject.org/fedora-minimal
RUN microdnf install -y procps-ng && microdnf clean all
COPY --from=builder /apps/_output/* /bin