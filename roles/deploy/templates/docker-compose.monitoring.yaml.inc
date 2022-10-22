  prometheus:
      image: {{ docker_image_prometheus }}
      container_name: prometheus
      volumes:
        - ./config/monitoring/Prometheus:/etc/prometheus
        - prometheus_data:/prometheus
      command:
        - '--config.file=/etc/prometheus/prometheus.yml'
        - '--storage.tsdb.path=/prometheus'
        - '--web.console.libraries=/etc/prometheus/console_libraries'
        - '--web.console.templates=/etc/prometheus/consoles'
        - '--storage.tsdb.retention.time=200h'
        - '--web.enable-lifecycle'
      restart: unless-stopped
      ports:
      - {{ prometheus_port }}:9090
      networks:
        - oracle

  grafana:
    image: {{ docker_image_grafana }}
    container_name: grafana
    volumes:
      - grafana_data:/var/lib/grafana
      - ./config/monitoring/grafana/provisioning/dashboards:/etc/grafana/provisioning/dashboards
      - ./config/monitoring/grafana/provisioning/datasources:/etc/grafana/provisioning/datasources
    environment:
      - GF_SECURITY_ADMIN_USER=${ADMIN_USER:-admin}
      - GF_SECURITY_ADMIN_PASSWORD=${ADMIN_PASSWORD:-admin}
      - GF_USERS_ALLOW_SIGN_UP=false
    restart: unless-stopped
    ports:
      - {{ grafana_port }}:3000
    networks:
      - oracle

  oracle_exporter:
    image: {{ docker_image_oracle_exporter }}
    ports:
      - {{ oracle_exporter_port }}:9161
    environment: 
      - DATA_SOURCE_NAME=system/{{ oracle_admin_pwd }}@//localhost:1521/{{ oracle_sid }}
    networks:
      - oracle