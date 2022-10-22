SCRIPTSRC=`readlink -f "$0" || echo "$0"`
SCRIPT_PATH=`dirname "$SCRIPTSRC" || echo .`

for files in $(find  ${SCRIPT_PATH}/dump/ -type f -name '*.dmp' -exec basename {} \; ); 

do docker exec  {{ oracle_container_name }} bash -c 'impdp PDBADMIN/{{ oracle_admin_pwd }}@{{ oracle_pdb_sid }} \
FULL=y \
DIRECTORY=LOCAL_PUMP_DIR \
DUMPFILE=LOCAL_PUMP_DIR:'$files' \
TABLE_EXISTS_ACTION=replace \
TRANSFORM=disable_archive_logging:Y \
NOLOGFILE=Y '; 

done



