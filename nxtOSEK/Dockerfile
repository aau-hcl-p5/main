FROM ubuntu:14.04

# Install required packages listed by nxtOSEK
RUN apt-get update
RUN apt-get -y install tk-dev ncurses-dev libmpfr-dev wget gzip tar software-properties-common

# Install wine
RUN dpkg --add-architecture i386
RUN wget -nc https://dl.winehq.org/wine-builds/Release.key
RUN apt-key add Release.key
RUN apt-add-repository https://dl.winehq.org/wine-builds/ubuntu/
RUN apt-get -y install apt-transport-https
RUN apt-get update
RUN apt-get -y install --install-recommends winehq-stable

# Download a specific version of texinfo, the one in 14.04 
# sources is not compatible with the expected version
RUN wget http://ftp.gnu.org/gnu/texinfo/texinfo-4.13.tar.gz
RUN gzip -dc < texinfo-4.13.tar.gz | tar -xf -
RUN cd texinfo-4.13 && ./configure && make && make install

# Build arm toolchain from nxtOSEK
COPY build_arm_toolchain.sh home/
RUN chmod 755 home/build_arm_toolchain.sh
RUN home/build_arm_toolchain.sh

# Move nxtOSEK files to home folder
WORKDIR /home/nxtosek
ADD nxtOSEK.tar.xz ./

# Add build.sh and set it as entrypoint to execute when executing docker container
COPY build.sh ./
RUN chmod 755 ./build.sh
ENTRYPOINT exec /home/nxtosek/build.sh