# Базовый образ — ubuntu
FROM ubuntu:latest

# Метка с информацией об авторе
LABEL maintainer="Давлятшин 241-372 <student@example.com>"

# Установка gcc
RUN apt-get update && apt-get install -y gcc g++ && rm -rf /var/lib/apt/lists/*

# Рабочая папка
WORKDIR /MyProj_Davlyatshin_241-372

# Копируем исходники
COPY src/ ./src/

# Копируем результаты работы по п.2
COPY result_task2/ ./result_task2/

# Компиляция проекта в файл exam_Program
RUN g++ -o exam_Program src/main.cpp

# Значение параметра программы по умолчанию
ENV DEFAULT_PARAM="default_value"

# Запуск exam_Program с параметром
CMD ./exam_Program $DEFAULT_PARAM