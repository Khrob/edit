


# edit file format proposal



Should it be binary or text? I'm inclined to start with text, at least as it gets developed. Text will also play nicely with version control

I definitely want to store every change, as I firmly believe you should never lose undo information when you close a project.

I'm thinking a timeline should be continuous, but something that has discrete frames (like a video) will automatically round down and snap to their frame boundary. 

	Contrived example:
		A 4ps video at 12.463 would snap and start at 12.25 seconds

The could be issues when two clips with different frame rates abut, but I'm keen to try this approach nonetheless.




Basic blobs:

## HEADER

* Magic Number/String 				Never change (0xED17 ?)
* File Type Version Number 		Change if this file format changes 


## BLOB INDEX	

File offsets for the different sections in here? Probably more use for binary version?

*  Blob Offsets
	*  Project 
	*  Paths
	*  Sources
	*  Clips
	*  Strings
	*  Transforms
	*  Operations
	*  Etc. 						Fill this in properly when we have a solid format here.

*  Source Count						# These are for parsing this file.
*  Clip Count						# Could use file offsets instead? 
*  Transform count					#
*  Operation count 					# Could be useful for checking file integrity?
*  Strings count 					# Or should we store a hash right at the end or something?


## PROJECT BLOB

Overall project information

*  Project Version Number			Should this just be something your version control cares about?
									May not really need it here.
*  Title							Name of this project. (How does this relate to the filename?)
*  Width/Height ratio				Output size (resolution independent)
*  Operations index					For undo/redo

Wondering if these are actually more important as _export_ functions, 
and we don't actually have to store them in the project file itself?
If we're _working_ in a particular format, it probably makes sense 
to store them with the project.

*  FPS								Store as ratio or just a double?
*  Audio Rate 						Hz. (Integer or floating point? I don't know sound well enough)
*  Width/Height 					In Pixels (Integer OK? Would you _ever_ want a partial pixel?)


## PATHS BLOB

Do we need to store these? Or just store the full path per video file? Might be useful for moving the project onto different people's machines.

*  Path strings						Do we need a 'base path' and multiple 'source paths', then the paths in 
										sources can be relative?



## SOURCES BLOB

Source file references.

*  Type								Video, Audio, Image, 3D Model, Text, Other Project...
*  Next 							Index of the next source in the file. (Given the path and data 
									will be of different size per source)
*  Base Path Index					The base path to start looking from.
*  Relative Path 					Base path + this gives source file. 
*  Full Path 						Store the whole thing. (not great for sharing the project)
									I'm not massively worried about storing a full path for every 
									clip in the project. Makes this file a bit bigger, but even with 
									a few thousand clips, we're only looking at the MB range.
*  Hash 							So we can find it again if/when the location changes (Meowhash!)
*  Active							Should this source be visible in the editor? 
									I think we should store deleted file references so we can undo and
									get clips we've had in the project in the past back. This will 
									make this file size grow, but if the worst comes to the worst, we 
									won't be losing any user data. 
*  Data								This will need to be different depending on the type.
										(Use unions in live memory? Depends on how much info would need storing)


## CLIPS BLOB

This is a snapshot of the current state of the project. If someone was to just read in the sources and clips blobs, they would be able to construct a valid project. (Without any undo info)

*  Index/ID 						Is it better to store an ID or just an index into the sources array?
									Given the sources array will only grow, it should be fine, but
									perhaps an id is better for when we want to copy and paste 
									clips into different projects? (But then, when they're added to the
									new project, they'd simply be added to the end of the sources array,
									or their index set accordingly if the source hash is already present?)
*  Start Time						Stored as a double, rounded down to fps boundary for display/rendering
									OR, do we do the rounding before it gets saved anywhere? Might cause 
									less confusion? Though, if we're exporting at different fps, it's 
									probably better to store the higher resolution.
									Also, we won't store an end time - it will be calculated with the 
									duration and offset (and possibly a speed transform) so storing it 
									here is asking for it to go out of sync with the true data.
*  Duration 						How long to play the clip for.

*  Offset 							Where in the source to start playing from.
*  Z Index 							Integer? Floating point? (So we can layer clips on top of each other)


## TRANSFORMS BLOB

A transform should be 1->n and be able to be applied to multiple source clips.

*  Type 							Matrix xform, Speed change.



## CONTROL VARIABLES

Any control point you can put on the timeline

How do we link these together so we can sample at any point?
How do we identify these so that they can be used by multiple clips?

*  Time 							Offset from the start of the clip/transform??
*  Interp in type
*  Interp out type
*  Min
*  Max
*  Value 
*  Transform ID 					So these link to a transform, then the transforms link to clips. (Which is where we'll get the 1-n coupling)

##	CONNECTIONS

If you want to connect clips together.

*  Parent ID/Index
*  Child ID/Index 






