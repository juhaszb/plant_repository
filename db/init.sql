CREATE TABLE sensor
(
    id   INT           NOT NULL AUTO_INCREMENT,
    name NVARCHAR(100) NOT NULL,
    PRIMARY KEY (id)
);

CREATE TABLE sensor_data
(
    id        INT NOT NULL AUTO_INCREMENT,
    sensor_id INT NOT NULL,
    timestamp INT NOT NULL,
    data      INT NOT NULL,
    PRIMARY KEY (id),
    FOREIGN KEY (sensor_id) REFERENCES sensor (id)
);

CREATE TABLE actor
(
    id        INT           NOT NULL AUTO_INCREMENT,
    name      NVARCHAR(100) NOT NULL,
    sensor_id INT           NOT NULL,
    PRIMARY KEY (id),
    FOREIGN KEY (sensor_id) REFERENCES sensor (id)
);

CREATE TABLE plant
(
    id    INT           NOT NULL AUTO_INCREMENT,
    name  NVARCHAR(100) NOT NULL,
    gridx INT           NOT NULL,
    gridy INT           NOT NULL,
    PRIMARY KEY (id)
);

CREATE TABLE requirement
(
    id        INT NOT NULL AUTO_INCREMENT,
    plant_id  INT NOT NULL,
    sensor_id INT NOT NULL,
    min_value INT NOT NULL,
    max_value INT NOT NULL,
    PRIMARY KEY (id),
    FOREIGN KEY (plant_id) REFERENCES plant (id),
    FOREIGN KEY (sensor_id) REFERENCES sensor (id)
);