#! /bin/bash

my_cpu="$(top -b -n 1 | head -3 | tail +3 | awk '{print $2}')"
my_mem_total="$(top -b -n 1 | head -4 | tail +4 | awk '{print $4}')"
my_mem_used="$(top -b -n 1 | head -4 | tail +4 | awk '{print $8}')"
my_disk_total="$(df /root | tail +2 | awk '{print $2}')"
my_disk_used="$(df /root | tail +2 | awk '{print $3}')"

echo "# HELP my_cpu CPU in percent."
echo "# TYPE my_cpu gauge"
echo "my_cpu $my_cpu"

echo "# HELP my_mem_total Total memory."
echo "# TYPE my_mem_total gauge"
echo "my_mem_total $my_mem_total"

echo "# HELP my_mem_used Used memory."
echo "# TYPE my_mem_used gauge"
echo "my_mem_used $my_mem_used"

echo "# HELP my_disk_total Total disk space."
echo "# TYPE my_disk_total gauge"
echo "my_disk_total $my_disk_total"

echo "# HELP my_disk_used Used disk space."
echo "# TYPE my_disk_used gauge"
echo "my_disk_used $my_disk_used"