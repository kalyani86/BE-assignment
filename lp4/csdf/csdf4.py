import os
from pathlib import Path

# --------------------------
# Setup
# --------------------------
os.system("cls")
print("=== 🔍 Computer Forensic Application ===")
print("Recover Deleted Files and Detect Deleted Partitions\n")

# Step 1: List drives
print("Available drives on this system:")
os.system("wmic logicaldisk get name")

# Step 2: Choose drive
drive = input("\nEnter the drive letter to analyze (e.g., D:): ").strip().upper()

# Step 3: Simulate creating a forensic image
img_dir = Path("forensic_images")
img_dir.mkdir(exist_ok=True)
img_name = input("Enter a name for the forensic image (e.g., drive_image.img): ").strip()
img_path = img_dir / img_name
with open(img_path, "w") as f:
    f.write("Simulated disk image content for forensic analysis.\n")
print(f"Forensic image created: {img_path}")

# Step 4: Detect deleted partitions (simulation)
print("\nDetecting deleted partitions (simulated)...")
# In a real forensic tool, you'd scan MBR/GPT, FS signatures, etc.
deleted_partitions = ["Partition 1 (NTFS)", "Partition 2 (EXT4)"]
for i, p in enumerate(deleted_partitions, 1):
    print(f"{i}. {p}")

# Step 5: Simulate deleted files recovery
print("\nScanning for deleted files (simulated)...")
deleted_files = {101: "report.docx", 102: "photo.jpg", 103: "notes.txt"}
for inode, name in deleted_files.items():
    print(f"Inode {inode}: {name} (deleted)")

inode_no = int(input("\nEnter the inode number of the file to recover: "))

if inode_no in deleted_files:
    recovered_file_name = deleted_files[inode_no].replace("_deleted", "_recovered")
    recovered_dir = Path("recovered_files")
    recovered_dir.mkdir(exist_ok=True)
    recovered_path = recovered_dir / recovered_file_name

    # Step 6: Recover file (simulation)
    with open(recovered_path, "w") as f:
        f.write(f"Recovered content for inode {inode_no}\n(Simulated data)")

    print(f"\n✅ File recovered successfully: {recovered_path}")
    print("\nContents of recovered file:")
    os.system(f"type {recovered_path}")  # Windows command to display content
else:
    print("Invalid inode number. No file recovered.")

print("\n=== Forensic recovery simulation complete ===")
