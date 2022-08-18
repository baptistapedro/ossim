FROM fuzzers/afl:2.52

RUN apt-get update
RUN apt install -y build-essential wget git clang cmake  automake autotools-dev  libtool zlib1g zlib1g-dev libexif-dev libjpeg-dev libjsoncpp-dev libgeotiff-dev libgeos++-dev
RUN git clone  https://github.com/ossimlabs/ossim.git
WORKDIR /ossim
RUN cmake -DCMAKE_C_COMPILER=afl-clang -DCMAKE_CXX_COMPILER=afl-clang++ .
RUN make
RUN make install
RUN mkdir /ossimCorpus
RUN wget https://download.samplelib.com/jpeg/sample-clouds-400x300.jpg
RUN wget https://download.samplelib.com/jpeg/sample-red-400x300.jpg
RUN wget https://download.samplelib.com/jpeg/sample-green-200x200.jpg
RUN wget https://download.samplelib.com/jpeg/sample-green-100x75.jpg
RUN  mv *.jpg /ossimCorpus

ENTRYPOINT  ["afl-fuzz", "-i", "/ossimCorpus", "-o", "/ossimOut"]
CMD ["/ossim/bin/ossim-cli", "info", "-p", "-i", "@@"]
