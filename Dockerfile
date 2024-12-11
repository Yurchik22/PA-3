FROM alpine AS build
RUN apk add --no-cache build-base automake autoconf
WORKDIR /home/optima
COPY . .
RUN autoreconf -i
RUN ./configure
RUN make

FROM alpine
COPY --from=build /home/optima/funcA /usr/local/bin/funcA
ENTRYPOINT ["/usr/local/bin/funcA"]

