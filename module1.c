#define __MODULE__
#define __KERNEL__
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h> /* copy_{from,to}_user() */
#include <linux/moduleparam.h>

#define BUF_SIZE 256
 
	static char bufferR[BUF_SIZE]="bonjour depuis le noyau"; 
	static char bufferW[BUF_SIZE]; 
	static size_t num = 0;
	int mon_arg=1;
	char* name ="mohamed";
	module_param(mon_arg, int,444);
	module_param(name, charp,444);
	
	MODULE_AUTHOR("skyrunner");	
	MODULE_DESCRIPTION("exemple de module");
	MODULE_SUPPORTED_DEVICE("none");
	MODULE_LICENSE("none");
	MODULE_PARM_DESC(mon_arg,"Mon premier argument");
	
	
	
	static int device_open(struct inode *inode, struct file *file); 
	static int device_release(struct inode *inode, struct file *file); 
	static ssize_t device_write(struct file *file, const char *buf, size_t count, loff_t *ppos); 
	static ssize_t device_read(struct file *file, char *buf, size_t count, loff_t *ppos);
	
	struct file_operations fops ={
		read : device_read,
		write:device_write,
		open:device_open,
		release:device_release,
	}; 

	
	static int __init mondriver_init(void) 
	{ 
		register_chrdev(52, "mon_driver", &fops);
		printk(KERN_INFO " mon_driver : Module1 chargé\n");
		printk(KERN_INFO "Le parametre à initialiser est mon_arg=%d / name=%s",mon_arg,name);
		return 0; 
	}
	static void __exit mondriver_exit(void) 
	{ 
		unregister_chrdev(52, "mon_driver"); 
		printk(KERN_INFO "mon_driver : Au revoir\n"); 
	}

	module_init(mondriver_init);
	module_exit(mondriver_exit);
	
	/*implementation des appels système */

	static int device_open(struct inode *inode, struct file *file) 
	{ 
		printk(KERN_INFO "mon_driver : open()\n"); 
		return 0; 
	} 

	static int device_release(struct inode *inode, struct file *file) 
	{ 
		printk(KERN_INFO "mon_driver : release()\n"); 
		return 0; 
	}
	static ssize_t device_write(struct file *file, const char *buf, size_t count, loff_t *ppos) 
	{  
		size_t taille_reelle;  
		taille_reelle = min((size_t)BUF_SIZE, count);  
		if (taille_reelle)    
			//if (
			copy_from_user(bufferW, buf, taille_reelle);//)     
		 		//return -1;  

		printk(KERN_DEBUG "mon_driver: Ecriture de %d/%d caractères %s depuis l’espace utilisateur \n", taille_reelle, count, bufferW);  
		return taille_reelle; 
	}
	static ssize_t device_read(struct file *file, char *buf, size_t count, loff_t *ppos) 
	{
		size_t taille_reelle;  
		taille_reelle = min(num, count);  
		if (taille_reelle)    
			//if (
			copy_to_user(buf, bufferR, taille_reelle);//)      
				//return -1;  

		num = 0; /* Lecture destructive */  
		printk(KERN_DEBUG "mon_driver: Lecture de %d/%d caractères: Message=%s,  depuis l’espace du noyau \n", taille_reelle, count, bufferR);  
		return taille_reelle;
	}













