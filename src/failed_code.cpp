// NOTE(hacksoi): One of the "theorems" the quaternion approach is based off
// (which I'm "pretty" sure is right) of is that the product of two
// quaternions, A and B, will produce a quaternion, C, whose axis is on the
// same plane as the axes of A's and B's. Because of this, the quaternion
// approach cannot work. The reason is that there is a constraint for C's axis:
// it _must_ be perpendicular to the Entity's position. C's axis _won't_ be
// perpendicular, even though velocity and acceleration axes are perpendicular,
// because the acceleration axis _must_ be rotated by the velocity axis before
// multiplying the two. This new acceleration axis _won't_ be perpendicular to
// the Entity's position; as such, the resulting velocity axis _won't_ be
// perpendicular.

internal void
MoveEntity(entity *Entity, float AccelerationAngle, float dt)
{
	v3 AccelerationAxis = Entity->RightAxis;

	if(AccelerationAngle != 0.0f)
	{
		Rotate(&AccelerationAxis, Entity->Velocity);

		quaternion Acceleration = Quaternion(AccelerationAxis, AccelerationAngle * dt / 80.0f);
		quaternion NewVelocity = Normalize(Acceleration * Entity->Velocity);

#if 0
		// NOTE(hacksoi): Fix NewVelocity
		// NOTE(hacksoi): Possible errors (should the angle be the _exact_
		// same?)
		{
			float VelocityAngle = GetAngle(NewVelocity);
			v3 WrongVelocityAxis = GetAxis(NewVelocity);
			v3 VelocityAxis = Normalize(Project(WrongVelocityAxis, Entity->Vertices[ENTITY_VERTEX_CENTER]));

			NewVelocity = Quaternion(VelocityAxis, VelocityAngle);
			// TODO: Logging
		}
#endif

		Entity->Velocity = NewVelocity;
	}

	quaternion EntityDelta = Entity->Velocity;//Slerp(IdentityQuat(), Entity->Velocity, dt);

	RotateNormalize(&Entity->RightAxis, EntityDelta);
	for(uint32_t EntityVertexIndex = 0;
		EntityVertexIndex < Entity->NumVertices;
		++EntityVertexIndex)
	{
		RotateNormalize(&Entity->Vertices[EntityVertexIndex], EntityDelta);
	}

	Assert(!isnan(Entity->Vertices[ENTITY_VERTEX_CENTER].X));

	v3 VelocityAxis = GetAxis(Entity->Velocity);
	float VelAxisDotEntCen = Dot(VelocityAxis, Entity->Vertices[ENTITY_VERTEX_CENTER]);
	DEBUGPrintf("%f\n", VelAxisDotEntCen);
}
